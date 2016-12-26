#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <rawfx/core/engine.h>
#include <rawfx/core/composite.h>
#include <rawfx/comp/background.h>


//template <typename T>
//class builder {
//public:

//    template <typename ...Args>
//    builder(Args&& ...args) : _ptr(new T(std::forward<Args>(args)...)) {
//    }

//    T& ref() {
//        return *_ptr.get();
//    }

//    T& build() {
//        return *_ptr.release();
//    }

//private:
//    std::unique_ptr<T> _ptr;
//};

void rawfx_init(rawfx::core::engine& e) {

    e.name("rawfx-sample").root((new rawfx::core::composite())->
        add(new rawfx::comp::background(rawfx::comp::background::color_type::BLACK))
    );
}


void glfw_error(int code, const char* message) {
    std::cout << "GLFW reported error " << code << " with message: " << message << std::endl;
}

int main(int argc, const char* argv[]) {

    glfwSetErrorCallback(&glfw_error);

    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(640, 480, "", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if(err != GLEW_OK) {
        std::cerr << "glewInit failed: " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    int exit_code = -1;
    try {

        rawfx::core::engine e;
        rawfx_init(e);

        glfwSetWindowTitle(window, e.name());
        glfwShowWindow(window);

        while (!glfwWindowShouldClose(window)) {

            e.handle(rawfx::core::event(rawfx::core::PROCESS));
            e.handle(rawfx::core::event(rawfx::core::RENDER));
            glfwSwapBuffers(window);
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
