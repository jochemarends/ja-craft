/**
 * @file cube.h
 * @author Jochem Arends
 * @date 23-04-2024
 */

#ifndef CUBE_H
#define CUBE_H

#include <array>
#include <ranges>
#include <functional>

#include <glad/glad.h>

#include <graphics/vertex.h>
#include <world/block.h>

namespace ja::cube {
    /**
     * Used for representing a facet of a cube.
     */
    enum class face {
        front, back, left, right, top, bottom,
    };

    /**
     * An array containing all facets of a cube.
     */
    inline const std::array<face, 6> faces{face::front, face::back, face::left, face::right, face::top, face::bottom};

    /**
     * Generates vertices of a face.
     *
     * @param f The face to obtain the vertices of.
     * @param b The block the texture should be of.
     * @return A sequence of vertices that represent the face.
     */
    std::span<const vertex, 4> face_vertices(face f);

    inline auto face_vertices(face f, block b) {
        return std::views::transform(face_vertices(f), [b](vertex vert) {
            vert.m_texcoord.z = static_cast<float>(block_traits::texture_index(b));
            return vert;
        });
    }

    inline const std::array<GLuint, 6> face_indices{0, 1, 2, 0, 2, 3};

    inline auto vertices(block b) {
        return faces | std::views::transform([b](face f) {
                            return face_vertices(f, b);
                       })
                     | std::views::join;
    }

    inline auto indices = std::views::repeat(face_indices, 6)
                        | std::views::enumerate
                        | std::views::transform([](auto tuple) {
                              auto [index, range] = tuple;
                              return std::views::transform(range, std::bind_front(std::plus{}, index * 4));
                          })
                        | std::views::join;
}

#endif

