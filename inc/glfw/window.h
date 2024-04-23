/**
 * @file window.h
 * @author Jochem Arends
 * @date 06-01-2024
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <array>
#include <memory>
#include <GLFW/glfw3.h>

namespace glfw::window {
    /**
     * A functor used to free window handles.
     */
    struct deleter {
        void operator()(GLFWwindow* window);
    };

    using handle = std::unique_ptr<GLFWwindow, deleter>;

    /**
     * Create a GLFW window.
     *
     * @param width Width of the window.
     * @param height Height of the window.
     * @param title Title of the window.
     * @return A window handle.
     */
    handle make(int width, int height, const std::string& title);

    /**
     * Get size of a GLFW window.
     *
     * @param window A window handle.
     * @return A two-component vector where the first and second element represent width and height respectively.
     */
    std::array<int, 2> size_of(const handle& window);
}

#endif 

