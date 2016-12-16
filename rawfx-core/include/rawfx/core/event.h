#pragma once

#include <chrono>

namespace rawfx {
namespace core {

enum event_type {
    ATTACH,
    DETACH,
    RENDER,
    PROCESS,
    INPUT
};

class event {
public:
    event(const event_type& type);
    event_type type() const;
    bool is(event_type type) const;

    template <typename T>
    const T& as() {
        return *static_cast<T*>(this);
    }

private:
    event_type _type;
};

//class process_event: public event {
//public:
//    process_event(const std::chrono::duration& step) : event(PROCESS), step(step) {
//    }

//    std::chrono::duration step;

//};


}
}
