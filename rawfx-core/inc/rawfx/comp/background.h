#pragma once

#include <GL/gl.h>

#include <rawfx/core/handler.h>
#include <rawfx/graphics/color.h>

namespace rawfx {

class background: public handler {
public:

    typedef color<rgba<GLclampf>> color_type;

    background(const color_type& clr, const GLbitfield& clear = GL_COLOR_BUFFER_BIT);
    virtual void on(const event &evt, engine &eng);

private:
    color_type _color;
    GLbitfield _clear;

};

}
