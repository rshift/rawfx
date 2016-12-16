#pragma once

#include <memory>
#include <algorithm>
#include <vector>

#include <rawfx/core/event.h>
#include <rawfx/core/handler.h>
#include <rawfx/core/engine.h>

namespace rawfx {
namespace core {

class composite: public handler {
public:

    virtual ~composite() = default;
    virtual void on(const event& evt, engine& eng);
    void add(handler* h);

private:
    engine* _engine;
    std::vector<std::unique_ptr<handler>> children;
};


}
}
