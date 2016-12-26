#pragma once

#include <GL/gl.h>

#include <rawfx/core/handler.h>
#include <rawfx/graphics/color.h>

namespace rawfx {
namespace comp {

class background: public rawfx::core::handler {
public:

    typedef rawfx::graphics::color<rawfx::graphics::rgba<GLclampf>> color_type;

    background(const color_type& clr, const GLbitfield& clear = GL_COLOR_BUFFER_BIT);
    virtual void on(const rawfx::core::event &evt, rawfx::core::engine &eng);

private:
    color_type _color;
    GLbitfield _clear;

};


}
}
