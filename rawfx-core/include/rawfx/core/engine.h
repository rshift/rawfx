#pragma once

#include <memory>

#include <rawfx/core/handler.h>

namespace rawfx {
namespace core {

class engine {
public:

    void kill_me() {
        _kill = true;
    }

    bool must_kill() {
        if (_kill) {
            _kill = false;
            return true;
        }
        return false;
    }

private:

    bool _kill;

};

}
}
