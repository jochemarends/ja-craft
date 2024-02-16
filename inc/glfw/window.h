/**
 * @file window.h
 * @author Jochem Arends
 * @date 06-01-2024
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <memory>

namespace glfw::window {
    /*
     * A fucntor used to free window handles.
     */
    struct deleter {
        void operator()(GLFWwindow* window);
    };

    using handle = std::unique_ptr<GLFWwindow, deleter>;

    /*
     * Create a GLFW window.
     *
     * @param width Width of the window.
     * @param height Height of the window.
     * @param title Title of the window.
     * @return A window handle.
     */
    handle make(int width, int height, const std::string& title);
}

#endif 

