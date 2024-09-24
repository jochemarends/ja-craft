/**
 * @file chunk.h
 * @author Jochem Arends
 * @date 23-05-2024
 */

#ifndef CHUNK_H
#define CHUNK_H

#include <ranges>

#include <graphics/mesh.h>
#include <graphics/vertex.h>
#include <world/block.h>
#include <world/cube.h>

namespace ja::chunk {
    constexpr std::size_t width  = 16;
    constexpr std::size_t height = 16;
    constexpr std::size_t depth  = 16;

    mesh mesh_from([[maybe_unused]] const block (&data)[width][height][depth]) {
        using namespace std::views;

        std::vector<vertex> vertices{};
        std::vector<GLuint> indices{};

        auto vertices = zip_transform(cartesian_product(iota(0uz, width), iota(0uz, height), iota(0uz, depth)), 
                      | std::zip_
                      | join;

        for (auto [i, j, k] : cartesian_product(iota(0uz, width), iota(0uz, height), iota(0uz, depth)) {
            vertices.append_range(cube::vertices(block::grass));
            indices.append_range(std::views::transform(cube::indices, std::bind_front(std::plus{}, vertices.size()));
        }

        return mesh::from(vertices, indices);
    }
}

#endif

