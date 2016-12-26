#include <rawfx/comp/background.h>

namespace rawfx {

background::background(const color_type& clr, const GLbitfield& clear) :
    _color(clr),
    _clear(clear) {
}

void background::on(const event &evt, engine &eng) {
    if (evt.is(RENDER)) {
        glClearColor(_color.r, _color.g, _color.b, _color.a);
        glClear(_clear);
    }
}

}
