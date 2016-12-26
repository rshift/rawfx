#include <rawfx/comp/background.h>

namespace rawfx {
namespace comp {


background::background(const color_type& clr, const GLbitfield& clear) :
    _color(clr),
    _clear(clear) {
}

void background::on(const rawfx::core::event &evt, rawfx::core::engine &eng) {
    if (evt.is(rawfx::core::RENDER)) {
        glClearColor(_color.r, _color.g, _color.b, _color.a);
        glClear(_clear);
    }
}

}
}
