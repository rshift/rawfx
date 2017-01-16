#pragma once

#include <rawfx/core/handler.h>
//#include <rawfx/custom.h>

namespace rawfx {

class engine {
public:

    void kill_me();
    bool must_kill();
    engine& root(handler* h);
    void handle(const event& evt);

    const char* name() const;
    engine& name(const char* n);

private:
    const char* _name = nullptr;
    bool _kill = false;

    std::unique_ptr<handler> _root;

};

}
