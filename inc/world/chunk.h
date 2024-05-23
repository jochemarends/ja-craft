/**
 * @file chunk.h
 * @author Jochem Arends
 * @date 23-05-2024
 */

#ifndef CHUNK_H
#define CHUNK_H

#include <ranges>

#include <graphics/mesh.h>
#include <world/cube.h>

namespace ja::chunk {
    constexpr std::size_t width  = 16;
    constexpr std::size_t height = 16;
    constexpr std::size_t depth  = 16;

    mesh mesh_from([[maybe_unused]] const block (&data)[width][height][depth]) {
        [[maybe_unused]] auto indices  = std::views::cartesian_product(
            std::views::iota(0uz, width),
            std::views::iota(0uz, height),
            std::views::iota(0uz, depth)
        );
        
        auto verts = cube::face_vertices(cube::face::front, block::grass) | std::ranges::to<std::vector>();
        return mesh::from(verts, cube::face_indices);
    }
}

#endif

