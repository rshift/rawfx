#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <rawfx/core/engine.h>
#include <rawfx/comp/composite.h>
#include <rawfx/comp/background.h>

void rawfx_init(rawfx::engine& e) {
    e.name("rawfx-sample").root((new rawfx::composite())->
        add(new rawfx::background(rawfx::background::color_type::BLACK))
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

        rawfx::engine e;
        rawfx_init(e);

        if (e.name() != nullptr) {
            glfwSetWindowTitle(window, e.name());
        }
        glfwShowWindow(window);

        while (!glfwWindowShouldClose(window)) {
            glfwSetTime(0.0);

            e.handle(rawfx::event(rawfx::PROCESS));
            e.handle(rawfx::event(rawfx::RENDER));
            glfwSwapBuffers(window);
            glfwPollEvents();

            //e.step(glfwGetTime());
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
