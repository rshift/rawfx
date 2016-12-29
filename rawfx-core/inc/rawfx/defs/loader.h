#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>

namespace rawfx {

template <typename T>
class restore_guard {
public:
    restore_guard(T& ref, const T& value) : _ref(ref), initial(ref) {
        _ref = value;
    }

    ~restore_guard() {
        _ref = initial;
    }

    const T initial;

private:
    T& _ref;

};



class loader {
public:

    template <typename T>
    class def_actions {
    public:
        typedef typename T::value_type value_type;

        def_actions(loader& l, const T& def) : _l(l), _def(def) {
        }

        const value_type* get() const {
            def_entry<T>* e = dynamic_cast<def_entry<T>*>(_l.find(&_def).second);
            return e != nullptr ? &e->value : nullptr;
        }

        const value_type& load() {

            typedef std::pair<const void*, entry*> entry_pair;
            thread_local entry_pair loading(nullptr, nullptr);

            def_entry<T>* found_entry = dynamic_cast<def_entry<T>*>(_l.find(&_def).second);
            if (found_entry == nullptr) {

                found_entry = new def_entry<T>();
                _l._entries[&_def].reset(found_entry);

                {
                    restore_guard<entry_pair> rg(loading, std::make_pair(&_def, found_entry));
                    found_entry->value = _def.load(_l);
                }
            }

            found_entry->referenced_by.insert(loading.first);
            if (loading.second != nullptr) {
                loading.second->references.insert(&_def);
            }
            return found_entry->value;
        }

        bool unload() {
            entry_coords found = _l.find(&_def);
            if (found.first == nullptr) {
                return false;
            }

            found.second->referenced_by.erase(nullptr);
            return found.first->unload(*found.second, &_def);
        }

        template <typename U>
        bool is_ref_by(const U& other) const {
            entry_coords found = _l.find(&_def);
            return found.second != nullptr && found.second->referenced_by.count(&other) > 0;
        }

        template <typename U>
        bool has_ref_to(const U& other) const {
            entry_coords found = _l.find(&_def);
            return found.second != nullptr && found.second->references.count(&other) > 0;
        }

        bool loaded() const {
            return _l._entries.count(&_def) > 0;
        }

    private:

        loader& _l;
        const T& _def;

    };

    loader(loader* p = nullptr);
    ~loader();

    template <typename T>
    def_actions<T> of(const T& def) {
        return def_actions<T>(*this, def);
    }

    template <typename T>
    const def_actions<T> of(const T& def) const {
        return def_actions<T>(*const_cast<loader*>(this), def);
    }

    size_t unload_all();

    loader* parent();
    void parent(loader* p);

private:

    class entry {
    public:

        virtual ~entry() = default;
        virtual void unload(loader& loader, const void* def_ptr) = 0;

        std::unordered_set<const void*> references;
        std::unordered_set<const void*> referenced_by;

    };

    template <typename T>
    class def_entry: public entry {
    public:
        typedef typename T::value_type value_type;

        virtual void unload(loader& loader, const void* def_ptr) {
            static_cast<const T*>(def_ptr)->unload(loader, value);
        }

        value_type value;
    };


    typedef std::pair<loader*, entry*> entry_coords;

    template <bool unload_this>
    void unload_refs(entry& e, const void* def) {
        e.unload(*this, def);
        for (auto it = e.references.begin(); it != e.references.end(); it++) {
            const void* ref_def = *it;
            entry_coords found = find(ref_def);
            if (found.first == nullptr) {
                continue;
            }

            found.second->referenced_by.erase(def);
            if (unload_this || found.first != this) {
                found.first->unload(*found.second, ref_def);
            }
        }
    }

    entry_coords find(const void* dp);
    bool unload(entry& e, const void* def);
    bool unload_with_refs(entry& e, const void* def);

    std::unordered_map<const void*, std::unique_ptr<entry>> _entries;
    loader* _parent;

};

}
