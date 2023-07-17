#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "gfx/shader.h"
#include "gfx/program.h"
#include "world/cube_mesh.h"
#include "world/camera.h"
#include "world/chunk.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ranges>
#include "world/aabb.h"
#include "util/indices_view.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "gfx/texture_atlas.h"
#include "world/terrain.h"


template<typename T>
struct vec_interface {};

template<typename T, std::size_t N>
struct vec : vec_interface<vec<T, N>> {
    T m_data[N];
};

template<typename T>
struct vec<T, 2> : vec_interface<vec<T, 2>> {
    union {
        struct { T x, y; };
        T m_data[2];
    };
};

template<typename T>
struct vec<T, 3> : vec_interface<vec<T, 3>> {
    union {
        struct { T x, y, z; };
        T m_data[3];
    };
};

template<typename T = float>
using vec2 = vec<T, 2>;

template<typename T = float>
using vec3 = vec<T, 3>;

ja::chunk* pchunk;
ja::terrain* pterrain;

constexpr std::size_t window_w = 800;
constexpr std::size_t window_h = 600;
const std::string window_title = "ja-craft";
ja::camera camera{0.1f, 100.0f, static_cast<float>(window_w) / window_h};
ja::block selected_block = ja::block::dirt;


void move(ja::camera& camera, ja::chunk& chunk, glm::vec3 velocity) {
    ja::aabb player_aabb{
        .min{glm::vec3{-0.4f, -0.4f, -0.4f} + camera.m_position},
        .max{glm::vec3{ 0.4f,  0.4f,  0.4f} + camera.m_position}
    };

    // 1. check for the nearest collision
    ja::swept_result res{1.0f, {}};
    float s{};
    for (auto [i, j, k] : indices_of(chunk.data())) {
        if (chunk.data()[i][j][k] == ja::block::empty) continue;

        auto new_res = ja::swept(player_aabb, chunk.aabb(i, j, k), velocity);
        float new_s = glm::length(new_res.normal * velocity);

//        if (new_res.time <= res.time && new_s > s) {
//            res = new_res;
//            s = new_s;
//        }

        if (new_res.time < res.time) {
            res = new_res;
            s = new_s;
        }

    }

    // 2. apply velocity
    camera.m_position += velocity * res.time;
    camera.m_position += res.normal * 0.001f; // avoid getting stuck between blocks

    if (res.time != 1.0f) {
        glm::vec3 a = res.normal, slide_velocity{};

        auto remaining_time = 1.0f - res.time;
        velocity *= remaining_time;

        // 3. calculate the slide velocity
        std::swap(a.x, a.y);
        if (a != res.normal) slide_velocity += a * glm::dot(a, velocity);
        std::swap(a.x, a.y);

        std::swap(a.y, a.z);
        if (a != res.normal) slide_velocity += a * glm::dot(a, velocity);
        std::swap(a.y, a.z);

        std::swap(a.x, a.z);
        if (a != res.normal) slide_velocity += a * glm::dot(a, velocity);
        std::swap(a.x, a.z);

        // 4. apply slide
        move(camera, chunk, slide_velocity);
    }
}

void move(ja::camera& camera, ja::terrain& terrain, glm::vec3 velocity) {
    move(camera, terrain.chunk_at(camera.m_position), velocity);
}

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

    for (int i = GLFW_KEY_1; i < GLFW_KEY_5; ++i) {
        if (glfwGetKey(window, i) == GLFW_PRESS) {
            selected_block = static_cast<ja::block>(i - GLFW_KEY_0 - 1);
        }
    }

    // convert input to offset
    if (glm::length(input) != 0) {
        glm::vec3 offset = glm::normalize(input) * player_speed * delta_time;

        ja::aabb player_aabb{
            .min{glm::vec3{-0.5, -0.5, -0.5} + camera.m_position},
            .max{glm::vec3{ 0.5,  0.5,  0.5} + camera.m_position}
        };

        ja::swept_result res{};
        ja::chunk& chunk = *pchunk;
        glm::vec3 d_position{0, 0, 0};
        d_position += offset.x * glm::normalize(glm::cross(camera.m_up, camera.m_front));
        d_position += offset.z * camera.m_front;
        d_position += offset.y * camera.m_up;

        move(camera, *pterrain, d_position);
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

using mouse_button_callback_type = std::function<void(GLFWwindow*, int, int, int)>;
std::vector<mouse_button_callback_type> mouse_button_callbacks;

void register_mouse_button_callback(mouse_button_callback_type callback) {
    mouse_button_callbacks.push_back(callback);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    for (const auto& fn : mouse_button_callbacks) {
        std::invoke(fn, window, button, action, mods);
    }
}

using mouse_move_callback_type = std::function<void(GLFWwindow*, float, float)>;
std::vector<mouse_move_callback_type> mouse_move_callbacks;

void register_mouse_move_callback(mouse_move_callback_type callback) {
    mouse_move_callbacks.push_back(callback);
}

void mouse_move_callback(GLFWwindow* window, double x, double y) {
    for (const auto& fn : mouse_move_callbacks) {
        std::invoke(fn, window, x, y);
    }
}


void mouse_button_cb(GLFWwindow* window, int button, int action, int mods) {
    auto [x, y] = pterrain->pos_to_idx(camera.m_position);
    ja::chunk& chunk = pterrain->m_chunks[x][y];
    ja::ray ray{camera.m_position, camera.m_front};

    ja::terrain& t = *pterrain;

    auto result = chunk.test(ray);
    if (!result) return;
    auto [i, j, k] = result->first;
    ja::face face = result->second;

    if (action == GLFW_RELEASE) {
        return;
    };

    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        int col = chunk.m_data[i][j][k];

        switch (face) {
            case ja::face::front:
                ++k;
                break;
            case ja::face::back:
                --k;
                break;
            case ja::face::left:
                ++i;
                break;
            case ja::face::right:
                --i;
                break;
            case ja::face::top:
                ++j;
                break;
            case ja::face::bottom:
                --j;
        }

            chunk.data()[i][j][k] = selected_block;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        chunk.data()[i][j][k] = ja::empty;
    }

    chunk.generate();
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);

    // filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    GLubyte* data = stbi_load("resources/textures/atlas.png", &width, &height, &channels, 0);
    if (data == nullptr) {
        std::ifstream ifs{"C:/dev/ja-craft/resources/textures/atlas.jpg"};
        std::cout << std::boolalpha << ifs.good();
        throw std::runtime_error{stbi_failure_reason()};
        throw std::runtime_error{"error: failed to load texture"};
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    program.use();

    glActiveTexture(GL_TEXTURE1);
    texture_atlas atlas{"resources/textures/atlas.png", 2, 2};
    glUniform1i(program.uniform_location("atlas"), 1);

    ja::chunk chunk;
    pchunk = &chunk;
    chunk.generate();
    ja::terrain terrain;
    pterrain = &terrain;

    camera.m_position.z += 2.0f;

    // game loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //terrain.center_to(camera.m_position);

        handle_key_input(window);
        glUniformMatrix4fv(program.uniform_location("proj"), 1, GL_FALSE, glm::value_ptr(camera.proj()));
        glUniformMatrix4fv(program.uniform_location("view"), 1, GL_FALSE, glm::value_ptr(camera.view()));
        terrain.draw(program);

        glm::mat4 model{1};
        glUniformMatrix4fv(program.uniform_location("model"), 1, GL_FALSE, glm::value_ptr(model));

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
