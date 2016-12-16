#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <rawfx/core/composite.h>


#include <iostream>


//namespace gl {
//namespace core {

//class renderer {


//};


//class menu_scene {


//public:

//    virtual void on(const event& evt, engine& e) {

//        if (evt.type() != INPUT) {
//            return;
//        }

//        const input_event& input;
//        if (input.source == MOUSE && input.action == PRESS && input.button == MOUSE_LEFT && r.contains(e.input.mouse.position)) {

//        }

//    }


//};


//class mad_scene: public composite_handler {
//public:


//    virtual void on(event evt, engine &eng) {
//        scope_guard g(eng, _scope);
//        transform_guard tf(eng, _transform);


//        eng.scope().get(PROGRAM_APPOLO);
//        eng.scope().unload(PROGRAM_APPOLO);
//        eng.scope().load(PROGRAM_APPOLO);

//        composite_handler::on(evt, eng);
//    }

//private:

//    scope _scope;

//};

//class scope {
//public:


//private:
//    scope* _parent;
//    std::unordered_map<const void*, any> _entries;
//};

//class engine {


//    void on(event evt) {
//        root_handler->on(evt, *this);
//    }

//private:

//    handler* root_handler;
//    scope root_scope;
//    scope& current_scope = root_scope;
//    std::duration _step;
//    renderer _renderer;


//};

//}
//}



namespace gl {

    class shader {
    public:
        shader() : _id(0) {
        }

        shader(GLuint id): _id(id) {
        }

        shader(shader&& other) {
            _id = other._id;
            other._id = 0;
        }

        shader(GLenum type, const char* src) : shader() {
            create(type).compile(src);
        }

        ~shader() {
            destroy();
        }

        GLint iv(GLenum pname) const {
            ensure_valid();

            GLint param;
            glGetShaderiv(_id, pname, &param);
            return param;
        }

        std::string info_log() const {
            std::string log(static_cast<size_t>( iv(GL_INFO_LOG_LENGTH) ), '\0');
            if (log.size() > 0) {
                glGetShaderInfoLog(_id, static_cast<GLsizei>( log.size() ), NULL, &log[0]);
            }
            return log;
        }

        shader& destroy() {
            if (_id != 0) {
                glDeleteShader(_id);
                _id = 0;
            }
        }

        shader& create(GLenum type) {
            destroy();
            _id = glCreateShader(type);
            return *this;
        }

        shader& compile(const char* src) {
            ensure_valid();
            glShaderSource(_id, 1, &src, NULL);
            glCompileShader(_id);
            if (!iv(GL_COMPILE_STATUS)) {
                throw std::logic_error("shader compilation error: " + info_log());
            }
            return *this;
        }

        bool valid() const {
            return _id != 0;
        }

        inline void ensure_valid() const {
            if (_id == 0) {
                throw std::logic_error("attempt to use invalid shader (id is zero)");
            }
        }

        static shader compile(const char* src, GLenum type) {
            shader s;
            s.create(type).compile(src);
            return s;
        }

    private:
        GLuint _id;


    };


}

void glfw_error(int code, const char* message) {
    std::cout << "GLFW reported error " << code << " with message: " << message << std::endl;
}

int main(void) {

    glfwSetErrorCallback(&glfw_error);

    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow *window;
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if(err != GLEW_OK) {
        // Problem: glewInit failed, something is seriously wrong.
        std::cerr << "glewInit failed: " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    int exit_code = -1;
    try {
        gl::shader s1(GL_FRAGMENT_SHADER, "abc");

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        exit_code = 0;

    } catch (std::exception const& e) {
        std::cerr << "Application shutting down due to unexpected error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred. Application shutting down..." << std::endl;
    }
    glfwTerminate();
    return exit_code;

}
