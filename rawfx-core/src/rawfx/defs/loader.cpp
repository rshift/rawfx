#include <rawfx/dev/assert.h>
#include <rawfx/defs/loader.h>


namespace rawfx {

loader::loader(loader* p) : _parent(p) {
}

loader::~loader() {
    RAWFX_ASSERT(unload_all(), == 0, "destructing rawfx::loader(" << this << ") which has entries with references");
}

loader::entry_coords loader::find(const void* dp) {
    auto found = _entries.find(dp);
    if (found != _entries.cend()) {
        return std::make_pair(const_cast<loader*>(this), found->second.get());
    }
    return _parent != nullptr ? _parent->find(dp) : std::make_pair(nullptr, nullptr);
}

bool loader::unload(entry& e, const void* def) {
    if (!e.referenced_by.empty()) {
        return false;
    }
    unload_refs<true>(e, def);
    return _entries.erase(def) == 1;
}

bool loader::unload_with_refs(entry& e, const void *def) {
    e.referenced_by.erase(nullptr);

    while (!e.referenced_by.empty()) {
        const void* ref_def = *e.referenced_by.begin();

        auto it = _entries.find(ref_def);
        if (it == _entries.end()) {
            return false;
        }
        if (!unload_with_refs(*it->second.get(), it->first)) {
            return false;
        }
        e.referenced_by.erase(ref_def);
        _entries.erase(it);
    }

    unload_refs<false>(e, def);
    return true;
}

size_t loader::unload_all() {

    auto it = _entries.begin();
    while (it != _entries.end()) {
        if (unload_with_refs(*it->second.get(), it->first)) {
            it = _entries.erase(it);
        } else {
            ++it;
        }
    }
    return _entries.size();

}

loader* loader::parent() {
    return _parent;
}

void loader::parent(loader* p) {
    // TODO reload all objects which has references to parent loader
    _parent = p;
}


}
