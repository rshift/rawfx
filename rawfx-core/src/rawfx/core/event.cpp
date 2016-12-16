#include <rawfx/core/event.h>

namespace rawfx {
namespace core {

event::event(const event_type& type) : _type(type) {
}

event_type event::type() const {
    return _type;
}

bool event::is(event_type type) const {
    return _type == type;
}

}
}
