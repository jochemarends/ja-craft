/**
 * @file cube.h
 * @author Jochem Arends
 * @date 23-04-2024
 */

#ifndef CUBE_H
#define CUBE_H

#include <ranges>
#include <array>

#include <glad/glad.h>

#include <graphics/vertex.h>
#include <world/block.h>

namespace ja::cube {
    enum class face {
        front, back, left, right, top, bottom,
    };

    inline const std::array<face, 6> faces{face::front, face::back, face::left, face::right, face::top, face::bottom};

    constexpr std::size_t face_vertex_count = 4;

    template<face>
    inline const std::array<vertex, face_vertex_count> face_vertices;

    template<>
    inline const std::array<vertex, face_vertex_count> face_vertices<face::front>{
        vertex{{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}},
        vertex{{-0.5f, 0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},
        vertex{{0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}},
        vertex{{0.5f,  -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}},
    };

    template<>
    inline const std::array<vertex, face_vertex_count> face_vertices<face::back>{
        vertex{{0.5f,  -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        vertex{{0.5f,  0.5f,  -0.5f}, {1.0f, 1.0f, 0.0f}},
        vertex{{-0.5f, 0.5f,  -0.5f}, {0.0f, 1.0f, 0.0f}},
        vertex{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}},
    };

    template<>
    inline const std::array<vertex, face_vertex_count> face_vertices<face::left>{
        vertex{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}},
        vertex{{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        vertex{{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}},
        vertex{{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
    };

    template<>
    inline const std::array<vertex, face_vertex_count> face_vertices<face::right>{
        vertex{{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
        vertex{{0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}},
        vertex{{0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        vertex{{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}},
    };

    template<>
    inline const std::array<vertex, face_vertex_count> face_vertices<face::top>{
        vertex{{-0.5f, 0.5f,  0.5f}, {0.0f, 0.0f, 0.0f}},
        vertex{{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        vertex{{0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}},
        vertex{{0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
    };

    template<>
    inline const std::array<vertex, face_vertex_count> face_vertices<face::bottom>{
        vertex{{0.5f,  -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
        vertex{{0.5f,  -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}},
        vertex{{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        vertex{{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 0.0f}},
    };

    inline const std::array<GLuint, 6> face_indices{0, 1, 2, 0, 2, 3};

    std::span<const vertex, face_vertex_count> vertices[]{
        face_vertices<face::front>, face_vertices<face::back>,
        face_vertices<face::left>, face_vertices<face::right>,
        face_vertices<face::top>, face_vertices<face::bottom>,
    };

    auto face_vertices(face f, block b) {
        switch (f) {
            case face::front:
                return vertices<face::front>;
            case face::back:
                return vertices<face::back>;
        }
    }

    inline auto indices = std::views::repeat(face_indices, std::ranges::size(vertices))
                        | std::views::enumerate
                        | std::views::transform([](auto tuple) {
                              auto [index, range] = tuple;
                              return std::views::transform(range, std::bind_front(std::plus{}, index * face_vertex_count));
                          })
                        | std::views::join;
}

#endif
