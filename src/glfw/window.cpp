/**
 * @file window.cpp
 * @author Jochem Arends
 * @date 06-01-2024
 */

#include <glfw/window.h>

namespace glfw::window {
    void deleter::operator()(GLFWwindow* window) {
        glfwDestroyWindow(window);
    }

    handle make(int width, int height, const std::string& title) {
        return handle{glfwCreateWindow(width, height, title.c_str(), NULL, NULL)};
    }
}

