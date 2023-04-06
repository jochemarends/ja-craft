#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "gfx/shader.h"
#include "gfx/program.h"
#include "world/cube_mesh.h"
#include "world/camera.h"
#include "world/chunk.h"
#include <iostream>
#include "world/aabb.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

ja::chunk* pchunk;

constexpr std::size_t window_w = 800;
constexpr std::size_t window_h = 600;
const std::string window_title = "ja-craft";
ja::camera camera{0.1f, 100.0f, static_cast<float>(window_w) / window_h};

void handle_key_input(GLFWwindow* window) {
    static float player_speed = 4.0f;
    static double prev_time = glfwGetTime();
    float delta_time = static_cast<float>(glfwGetTime() - prev_time);
    prev_time = glfwGetTime();

    // read input
    glm::vec3 input{0.0f, 0.0f, 0.0f};
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, true);
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
    struct { double x, y; } static prev{x, y};
    constexpr float sensitivity = 0.1f;
    float pitch = static_cast<float>(prev.y - y) * sensitivity;
    float yaw   = static_cast<float>(x - prev.x) * sensitivity;
    camera.rotate(pitch, yaw, 0.0f);
    prev = {x, y};
}

void mouse_button_cb(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        ja::ray ray{camera.m_position, camera.m_front};


        auto opt = pchunk->test(ray);

        if (opt) {
            std::cout << "TEST";
           auto idx = opt->index();
           pchunk->m_data[idx.x][idx.y][idx.z] = !pchunk->m_data[idx.x][idx.y][idx.z];
        }

//        for (std::size_t i = 0; i < ja::chunk::width; ++i) {
//            for (std::size_t j = 0; j < ja::chunk::height; ++j) {
//                for (std::size_t k = 0; k < ja::chunk::depth; ++k) {
//                    ja::aabb aabb = pchunk->aabb(i, j, k);
//                    if (ja::test(ray, aabb)) pchunk->m_data[i][j][k] = !pchunk->m_data[i][j][k];
//                }
//            }
//        }
        pchunk->generate();
    }
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

    glfwSetMouseButtonCallback(window, mouse_button_cb);
    glfwSetCursorPosCallback(window, handle_mouse_input);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

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

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    GLubyte* data = stbi_load("resources/textures/simple.jpg", &width, &height, &channels, 0);
    if (data == nullptr) {
        throw std::runtime_error{"error: failed to load texture"};
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    program.use();

    ja::chunk chunk;
    pchunk = &chunk;
    chunk.generate();

    // game loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        handle_key_input(window);
        glUniformMatrix4fv(program.uniform_location("proj"), 1, GL_FALSE, glm::value_ptr(camera.proj()));
        glUniformMatrix4fv(program.uniform_location("view"), 1, GL_FALSE, glm::value_ptr(camera.view()));


        chunk.mesh().draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteTextures(1, &texture);
    glfwDestroyWindow(window);
}
catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
}
catch (...) {
    std::cerr << "unknown exception!\n";
    return EXIT_FAILURE;
}