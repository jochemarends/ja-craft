/**
 * @file cube.h
 * @author Jochem Arends
 * @date 23-04-2024
 */

#ifndef CUBE_H
#define CUBE_H

#include <array>
#include <ranges>

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

//    std::span<const vertex, face_vertex_count> vertices[]{
//        face_vertices<face::front>, face_vertices<face::back>,
//        face_vertices<face::left>, face_vertices<face::right>,
//        face_vertices<face::top>, face_vertices<face::bottom>,
//    };
//
//    inline auto indices = std::views::repeat(face_indices, std::ranges::size(vertices))
//                        | std::views::enumerate
//                        | std::views::transform([](auto tuple) {
//                              auto [index, range] = tuple;
//                              return std::views::transform(range, std::bind_front(std::plus{}, index * face_vertex_count));
//                          })
//                        | std::views::join;
}

#endif
