#include <rawfx/core/engine.h>

namespace rawfx {
namespace core {


void engine::kill_me() {
    _kill = true;
}

bool engine::must_kill() {
    if (_kill) {
        _kill = false;
        return true;
    }
    return false;
}

engine& engine::root(handler* h) {
    _root.reset(h);
    _root->on(event(ATTACH), *this);
    return *this;
}

void engine::handle(const event& evt) {
    if (_root) {
        _root->on(evt, *this);
    }
}

const char* engine::name() const {
    return _name;
}

engine& engine::name(const char* n) {
    _name = n;
    return *this;
}



}
}

