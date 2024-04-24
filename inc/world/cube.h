/**
 * @file cube.h
 * @author Jochem Arends
 * @date 23-04-2024
 */

#ifndef CUBE_H
#define CUBE_H

#include <glad/glad.h>
#include <graphics/vertex.h>
#include <ranges>
#include <functional>

namespace ja::cube {
    namespace face {
        inline static constexpr std::size_t vertex_count = 4;

        inline static const vertex front[vertex_count]{
            {{-0.5f, -0.5f, 0.5f}},// {0.0f, 0.0f, 0.0f}},
            {{-0.5f, 0.5f,  0.5f}},// {0.0f, 1.0f, 0.0f}},
            {{0.5f,  0.5f,  0.5f}},// {1.0f, 1.0f, 0.0f}},
            {{0.5f,  -0.5f, 0.5f}},// {1.0f, 0.0f, 0.0f}},
        };

        inline static const vertex back[vertex_count]{
            {{0.5f,  -0.5f, -0.5f}},// {1.0f, 0.0f, 0.0f}},
            {{0.5f,  0.5f,  -0.5f}},// {1.0f, 1.0f, 0.0f}},
            {{-0.5f, 0.5f,  -0.5f}},// {0.0f, 1.0f, 0.0f}},
            {{-0.5f, -0.5f, -0.5f}},// {0.0f, 0.0f, 0.0f}},
        };

        inline static const vertex left[vertex_count]{
            {{-0.5f, -0.5f, -0.5f}},// {0.0f, 0.0f, 0.0f}},
            {{-0.5f, 0.5f,  -0.5f}},// {0.0f, 1.0f, 0.0f}},
            {{-0.5f, 0.5f,  0.5f}},//  {1.0f, 1.0f, 0.0f}},
            {{-0.5f, -0.5f, 0.5f}},//  {1.0f, 0.0f, 0.0f}},
        };

        inline static const vertex right[vertex_count]{
            {{0.5f, -0.5f, 0.5f}},//  {1.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f,  0.5f}},//  {1.0f, 1.0f, 0.0f}},
            {{0.5f, 0.5f,  -0.5f}},// {0.0f, 1.0f, 0.0f}},
            {{0.5f, -0.5f, -0.5f}},// {0.0f, 0.0f, 0.0f}},
        };

        inline const vertex top[vertex_count]{
            {{-0.5f, 0.5f, 0.5f}},//  {0.0f, 0.0f, 0.0f}},
            {{-0.5f, 0.5f, -0.5f}},// {0.0f, 1.0f, 0.0f}},
            {{0.5f,  0.5f, -0.5f}},// {1.0f, 1.0f, 0.0f}},
            {{0.5f,  0.5f, 0.5f}},//  {1.0f, 0.0f, 0.0f}},
        };

        inline const vertex bottom[vertex_count]{
            {{0.5f,  -0.5f,  0.5f}},//  {1.0f, 0.0f, 0.0f}},
            {{0.5f,  -0.5f, -0.5f}},// {1.0f, 1.0f, 0.0f}},
            {{-0.5f, -0.5f, -0.5f}},// {0.0f, 1.0f, 0.0f}},
            {{-0.5f, -0.5f,  0.5f}},//  {0.0f, 0.0f, 0.0f}},
        };

        inline static const std::array<GLuint, 6> indices{0, 1, 2, 0, 2, 3};
    }

    std::span<const vertex, face::vertex_count> vertices[]{
        face::front, face::back,
        face::left, face::right,
        face::top, face::bottom,
    };

    inline auto indices = std::views::repeat(face::indices, std::ranges::size(vertices))
                        | std::views::enumerate
                        | std::views::transform([](auto tuple) {
                              auto [index, range] = tuple;
                              std::cout << (int)index << '\n';
                              return std::views::transform(range, std::bind_front(std::plus{}, index * face::vertex_count));
                          })
                        | std::views::join;
}

#endif
