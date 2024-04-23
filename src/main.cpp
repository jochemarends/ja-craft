/**
 * @file main.cpp
 * @author Jochem Arends
 * @date 05-01-2024
 */

#include <graphics/mesh.h>
#include <graphics/program.h>
#include <graphics/shader.h>
#include <graphics/viewing_frustum.h>
#include <utility/scope_guard.h>
#include <world/cube.h>

#include <glad/glad.h>
#include <glfw/window.h>
#include <glm/gtc/type_ptr.hpp>

#include <array>
#include <exception>
#include <iostream>
#include <ranges>
#include <string>

using namespace std::literals::string_literals;

ja::viewing_frustum camera{};

void handle_key_input(const glfw::window::handle& window) {
    static auto prev_time = static_cast<float>(glfwGetTime());
    const auto curr_time = static_cast<float>(glfwGetTime());
    const auto delta_time = curr_time - prev_time;


    if (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window.get(), true);
    }

    glm::vec3 input{};
    if (glfwGetKey(window.get(), GLFW_KEY_W) == GLFW_PRESS) {
        input.z += 1.0f;
    }
    if (glfwGetKey(window.get(), GLFW_KEY_A) == GLFW_PRESS) {
        input.x += 1.0f;
    }
    if (glfwGetKey(window.get(), GLFW_KEY_S) == GLFW_PRESS) {
        input.z -= 1.0f;
    }
    if (glfwGetKey(window.get(), GLFW_KEY_D) == GLFW_PRESS) {
        input.x -= 1.0f;
    }

    if (glm::length(input) > 0.0f) {
        input = glm::normalize(input);
        constexpr float speed = 4.0f;
        camera.move(input * speed * delta_time);
    }

    prev_time = curr_time;
}

void on_mouse_move([[maybe_unused]] GLFWwindow* window, double x, double y) {
    using namespace ja;

    constexpr float sensitivity{0.2f};
    static glm::dvec2 old{x, y};
    const float pitch   = static_cast<float>(y - old.y) * sensitivity;
    const float heading = static_cast<float>(old.x - x) * sensitivity;
    camera.rotate(angle::from<degrees>(pitch), angle::from<degrees>(heading), angle{});

    old = {x, y};
}

void on_framebuffer_size_change([[maybe_unused]] GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
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

    glfwSetFramebufferSizeCallback(window.get(), on_framebuffer_size_change);
    glfwSetCursorPosCallback(window.get(), on_mouse_move);
    glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    auto [width, height] = glfw::window::size_of(window);
    camera.aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
    camera.fov = 45.0_deg;
    camera.position.z += 3.0f;


    //std::vector vec{cube::vertices.begin(), cube::vertices.end()};
    auto mesh = mesh::from(vertices);
    mesh.bind();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // render loop
    while (!glfwWindowShouldClose(window.get())) {
        glClear(GL_COLOR_BUFFER_BIT);

        handle_key_input(window);

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
    std::cerr << "ERROR: unknown exception\n";
    return EXIT_FAILURE;
}

