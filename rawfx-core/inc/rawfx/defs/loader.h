#pragma once


/*
 *
 * 1. Must disallow unloading of used objects
 * 2. Correct order of unloading when destructing
 * 3. Automatically unload dependency objects which wasn't loaded explicitly
 *
 * Provided functions
 *
 * load
 * unload
 * unload_all
 *
 */


#include <unordered_map>
#include <unordered_set>
#include <memory>

namespace rawfx {
namespace defs {

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
            def_entry<T>* e = dynamic_cast<def_entry<T>*>(_l.find(&_def));
            return e != nullptr ? &e->value_type : nullptr;
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

    loader(loader* p = nullptr) : _parent(p) {
    }

    ~loader() {
        unload_all();
    }


    template <typename T>
    def_actions<T> of(const T& def) {
        return def_actions<T>(*this, def);
    }

    template <typename T>
    const def_actions<T> of(const T& def) const {
        return def_actions<T>(*const_cast<loader*>(this), def);
    }

    void unload_all() {

        //while (_entries.begin() != _entries.end()) {

        // TODO implement

        // recursive
        //
        // bool force_unload(const T& def) {
        //   find entry by &def only in _entries of this loader (i.e. not using find)
        //   if not found return false
        //
        //   for (key in entry->referenced_by)
        //     if (!force_unload(ptr)
        //       throw logic_exception("ptr is referenced externally");
        //   }
        //   unload(def);
        // }
        //
        // unload_all impl:
        //
        // while (!_entries.empty()) {
        //  if (!force_unload(_entries.first()) {
        //    throw logic_exception("ptr is referenced externally");
        //  }
        // }


    }

    loader* parent() const {
        return _parent;
    }

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
    typedef std::pair<const loader*, const entry*> const_entry_coords;

    entry_coords find(const void* dp);
    const_entry_coords find(const void* dp) const;
    bool unload(entry& e, const void* def);

    std::unordered_map<const void*, std::unique_ptr<entry>> _entries;
    loader* _parent;

};

}
}