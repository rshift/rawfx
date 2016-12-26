#include <rawfx/defs/loader.h>


namespace rawfx {

loader::entry_coords loader::find(const void* dp) {
    auto found = _entries.find(dp);
    if (found != _entries.cend()) {
        return std::make_pair(this, found->second.get());
    }
    return _parent != nullptr ? _parent->find(dp) : std::make_pair(nullptr, nullptr);
}

loader::const_entry_coords loader::find(const void* dp) const {
    auto found = _entries.find(dp);
    if (found != _entries.cend()) {
        return std::make_pair(this, found->second.get());
    }
    return _parent != nullptr ? _parent->find(dp) : std::make_pair(nullptr, nullptr);
}


bool loader::unload(entry& e, const void* def) {
    if (!e.referenced_by.empty()) {
        return false;
    }

    e.unload(*this, def);
    for (auto it = e.references.begin(); it != e.references.end(); it++) {
        const void* ref_def = *it;
        entry_coords found = find(ref_def);
        if (found.first == nullptr) {
            continue;
        }

        found.second->referenced_by.erase(def);
        if (found.second->referenced_by.empty()) {
            found.first->unload(*found.second, ref_def);
        }
    }
    _entries.erase(def);
}

}
