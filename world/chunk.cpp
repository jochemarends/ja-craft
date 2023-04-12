#include "chunk.h"
#include <algorithm>
#include <functional>
#include "mesh.h"
#include <iostream>

void ja::chunk::generate() {
    m_mesh.clear();

    for (std::size_t i = 0; i < width; ++i) {
        for (std::size_t j = 0; j < height; ++j) {
            for (std::size_t k = 0; k < depth; ++k) {
                if (m_data[i][j][k] == false) continue;

                auto move_vertex = [offset = glm::vec3{i, j, k}](auto vertex) {
                    vertex.position += offset;
                    return vertex;
                };

                m_mesh.add_indices(std::span(indices), m_mesh.vertices().size());
                m_mesh.add_vertices(std::span(front), move_vertex);

                m_mesh.add_indices(std::span(indices), m_mesh.vertices().size());
                m_mesh.add_vertices(std::span(back), move_vertex);

                m_mesh.add_indices(std::span(indices), m_mesh.vertices().size());
                m_mesh.add_vertices(std::span(left), move_vertex);

                m_mesh.add_indices(std::span(indices), m_mesh.vertices().size());
                m_mesh.add_vertices(std::span(right), move_vertex);

                m_mesh.add_indices(std::span(indices), m_mesh.vertices().size());
                m_mesh.add_vertices(std::span(top), move_vertex);

                m_mesh.add_indices(std::span(indices), m_mesh.vertices().size());
                m_mesh.add_vertices(std::span(bottom), move_vertex);
            }
        }
    }
    m_mesh.update_buffers();
}

auto ja::chunk::test(ja::ray ray) const -> std::optional<iterator> {
    for (std::size_t i = 0; i < width; ++i) {
        for (std::size_t j = 0; j < height; ++j) {
            for (std::size_t k = 0; k < depth; ++k) {
                iterator it{*this, glm::uvec3{i, j, k}};
//                if (m_data[i][j][k] == false) continue;
                auto result = ja::test(ray, it.aabb());
                if (result) return it;
            }
        }
    }
    return std::nullopt;
}

ja::aabb ja::chunk::aabb(std::size_t i, std::size_t j, std::size_t k) const {
    return ja::aabb{
        .min{-0.5 + i, -0.5 + j, -0.5 + k},
        .max{ 0.5 + i,  0.5 + j,  0.5 + k}
    };
}

ja::chunk::iterator::iterator(const chunk& chunk, glm::uvec3 idx) : m_chunk{chunk}, m_idx{idx} {}

glm::vec3 ja::chunk::iterator::position() const {
    return m_idx;
}

glm::uvec3 ja::chunk::iterator::index() const {
    return m_idx;
}

ja::aabb ja::chunk::iterator::aabb() const {
    return ja::aabb{
        .min{-0.5 + m_idx.x, -0.5 + m_idx.y, -0.5 + m_idx.z},
        .max{ 0.5 + m_idx.x,  0.5 + m_idx.y,  0.5 + m_idx.z}
    };
}