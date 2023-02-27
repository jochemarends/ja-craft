#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "gfx/shader.h"
#include <iostream>
#include <fstream>
#include <filesystem>

constexpr std::size_t window_w = 800;
constexpr std::size_t window_h = 600;
const std::string window_title = "ja-craft";

int main() try {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(window_w, window_h, window_title.c_str(), NULL, NULL);
    if (window == NULL) {
        throw std::runtime_error{"error: failed to create window"};
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwDestroyWindow(window);
        throw std::runtime_error{"error: failed to load OpenGL"};
    }

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    using shader_type = ja::shader::type;
    ja::shader vert {shader_type::vert, "resources/shaders/simple.vert"};
    if (!vert.good()) {
        throw std::runtime_error{vert.info_log()};
    }

    // game loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
catch (std::exception& e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
}
catch (...) {
    std::cerr << "unknown exception!\n";
}