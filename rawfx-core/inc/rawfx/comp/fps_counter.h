#pragma once

#include <rawfx/core/event.h>
#include <rawfx/core/handler.h>
#include <rawfx/core/engine.h>

namespace rawfx {

template <typename T>
class step_info {


public:

    template <typename U>
    U seconds() const {

    }


};


template <typename T>
class fps_counter: public handler {
public:

    virtual void on(const event& evt, engine& eng) {

        eng.step().seconds<float>();

        //eng.step
    }

};


}
