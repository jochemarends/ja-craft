/**
 * @file main.cpp
 * @author Jochem Arends
 * @date 05-01-2024
 */

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glfw/window.h>
#include <graphics/buffer.h>
#include <graphics/mesh.h>
#include <graphics/program.h>
#include <graphics/shader.h>
#include <graphics/vertex_array.h>
#include <utility/scope_guard.h>
#include <graphics/viewing_frustum.h>
#include <exception>
#include <iostream>
#include <vector>
#include <string>

using namespace std::literals::string_literals;

void on_mouse_move(GLFWwindow* window, double x, double y) {
    constexpr float sensitivity{0.1f};
    static glm::dvec3 old{x, y};
    const float pitch = static_cast<float>(old.y - y) * sensitivity;
    const float heading = static_cast<float>(x - old.x) * sensitivity;
}

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

    auto vert = shader::from_file(GL_VERTEX_SHADER, "resources/shaders/simple.vert");
    if (!shader::good(vert)) {
        throw std::runtime_error{"simple.vert: "s + shader::what(vert)};
    }

    auto frag = shader::from_file(GL_FRAGMENT_SHADER, "resources/shaders/simple.frag");
    if (!shader::good(frag)) {
        throw std::runtime_error{"simple.frag: "s + shader::what(frag)};
    }

    auto program = program::make(vert, frag);
    glUseProgram(program.get());

    vertex vertices[]{
        {{-0.5f, -0.5f, 0.0}},
        {{ 0.5f, -0.5f, 0.0}},
        {{ 0.0f,  0.5f, 0.0}},
    };

    viewing_frustum camera{};
    camera.aspect_ratio = 700.0 / 400.0;

    camera.position.z += 3.0f;
    camera.rotate(0.0_deg, 45.0_deg, 0.0_deg);

    auto mesh = mesh::from(vertices);
    mesh.bind();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    while (!glfwWindowShouldClose(window.get())) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUniformMatrix4fv(program::uniform_location(program, "proj").value(), 1, GL_FALSE, glm::value_ptr(camera.proj()));

        glUniformMatrix4fv(program::uniform_location(program, "view").value(), 1, GL_FALSE, glm::value_ptr(camera.view()));

        glm::mat4 model{1};
        glUniformMatrix4fv(program::uniform_location(program, "model").value(), 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 3);

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

