#pragma once

namespace rawfx {
namespace core {

// fwd decl
class engine;

class handler {
public:

    virtual ~handler() = default;
    virtual void on(const event& evt, engine& eng) = 0;

};


}
}
