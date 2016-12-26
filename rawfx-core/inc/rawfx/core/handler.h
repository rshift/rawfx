#pragma once

#include <rawfx/core/event.h>
#include <memory>

namespace rawfx {

// fwd decl
class engine;

class handler {
public:

    handler() = default;

    virtual ~handler() = default;
    virtual void on(const event& evt, engine& eng) = 0;

private:
    // disabling assign and copy constructor

    handler& operator=(const handler& other) = default;
    handler(const handler& h) = default;
};

}
