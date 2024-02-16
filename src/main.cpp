/**
 * @file main.cpp
 * @author Jochem Arends
 * @date 05-01-2024
 */

#include <glad/glad.h>
#include <glfw/window.h>
#include <graphics/shader.h>
#include <graphics/program.h>
#include <graphics/vertex_array.h>
#include <graphics/buffer.h>
#include <utility/scope_guard.h>
#include <iostream>
#include <exception>

int main() try {
    using namespace ja;

    glfwInit();
    auto guard = make_scope_guard(glfwTerminate);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto window = glfw::window::make(700, 400, "ja-craft");
    if (!window) {
        throw std::runtime_error{"ERROR: failed to create a window"};
    }

    glfwMakeContextCurrent(window.get());

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error{"ERROR: failed to load OpenGL"};
    }

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    while (!glfwWindowShouldClose(window.get())) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }
}
catch (std::exception& e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
}
catch (...) {
    std::cerr << "ERROR: unkown exception\n";
    return EXIT_FAILURE;
}

