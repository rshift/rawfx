#pragma once

#include <memory>
#include <algorithm>
#include <vector>

#include <rawfx/core/event.h>
#include <rawfx/core/handler.h>
#include <rawfx/core/engine.h>

namespace rawfx {

class composite: public handler {
public:

//    virtual ~composite();
    virtual void on(const event& evt, engine& eng);
    composite* add(handler* h);

    bool empty() const;

private:
    engine* _engine = nullptr;
    std::vector<std::unique_ptr<handler>> children;
};

}
