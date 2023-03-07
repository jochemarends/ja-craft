#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "gfx/shader.h"
#include "gfx/program.h"
#include "world/cube_mesh.h"
#include "world/camera.h"
#include <iostream>

constexpr std::size_t window_w = 800;
constexpr std::size_t window_h = 600;
const std::string window_title = "ja-craft";
ja::camera camera{0.1f, 100.0f, static_cast<float>(window_w) / window_h};

void handle_key_input(GLFWwindow* window) {
    static float player_speed = 1.0f;
    static double prev_time = glfwGetTime();
    float delta_time = static_cast<float>(glfwGetTime() - prev_time);
    prev_time = glfwGetTime();

    // read input
    glm::vec3 input{0.0f, 0.0f, 0.0f};
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) ++input.z;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) --input.z;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) ++input.x;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) --input.x;

    // convert input to offset
    if (glm::length(input) != 0) {
        glm::vec3 offset = glm::normalize(input)* player_speed * delta_time;
        camera.move(offset);
    }
}

void handle_mouse_input(GLFWwindow* window, double x, double y) {
    struct { double x, y; } static prev = {x, y};
    constexpr float sensitivity = 0.1;
    float pitch = static_cast<float>(prev.y - y) * sensitivity;
    float yaw   = static_cast<float>(x - prev.x) * sensitivity;
    camera.rotate(pitch, yaw, 0.0f);
    prev = {x, y};
}

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

    glfwSetCursorPosCallback(window, handle_mouse_input);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    GLuint vbo, ebo, vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof ja::vertices, ja::vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof ja::indices, ja::indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    using shader_type = ja::shader::type;
    ja::shader vert{shader_type::vert, "resources/shaders/simple.vert"};
    if (!vert.good()) {
        throw std::runtime_error{vert.info_log()};
    }

    ja::shader frag{shader_type::frag, "resources/shaders/simple.frag"};
    if (!frag.good()) {
        throw std::runtime_error{frag.info_log()};
    }

    ja::program program{vert, frag};
    if (!program.good()) {
        throw std::runtime_error{program.info_log()};
    }

    program.use();

    // game loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        handle_key_input(window);
        glUniformMatrix4fv(program.uniform_location("proj"), 1, GL_FALSE, glm::value_ptr(camera.proj()));
        glUniformMatrix4fv(program.uniform_location("view"), 1, GL_FALSE, glm::value_ptr(camera.view()));

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
}
catch (std::exception& e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
}
catch (...) {
    std::cerr << "unknown exception!\n";
    return EXIT_FAILURE;
}