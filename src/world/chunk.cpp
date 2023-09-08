#include "chunk.h"
#include <algorithm>
#include <functional>
#include "../gfx/mesh.h"
#include <iostream>
#include <ranges>
#include "terrain.h"

namespace ja {

    bool is_transparant(block b) {
        return b == block::empty | b == block::glass;
    }

    chunk::chunk(ja::terrain& terrain)
        :m_terrain{terrain} {
        std::fill_n(&m_data[0][0][0], width * height * depth, block::empty);
    }

    const ja::terrain& chunk::terrain() const {
        return m_terrain;
    }

    ja::terrain& chunk::terrain() {
        return m_terrain;
    }

    block(&chunk::data())[width][height][depth] {
        return m_data;
    }

    const block(&chunk::data() const)[width][height][depth] {
        return m_data;
    }

    glm::vec3 chunk::block_offset() const {
        return glm::vec3{
            m_id.x * width,
            m_id.y * height,
            m_id.z * depth
        };
    }

    glm::vec3 chunk::pos(std::size_t i, std::size_t j, std::size_t k) const {
        return glm::vec3{i, j, k} + block_offset();
    }

    ja::aabb chunk::aabb() const {
        ja::aabb res{
            .min{-0.5f,                 -0.5f,        -0.5f},
            .max{ width - 0.5f, height - 0.5f, depth - 0.5f}
        };
        res.min += block_offset();
        res.max += block_offset();
        return res;
    }

    ja::aabb chunk::aabb(std::size_t i, std::size_t j, std::size_t k) const {
        ja::aabb res{
            .min{-0.5 + i, -0.5 + j, -0.5 + k},
            .max{ 0.5 + i,  0.5 + j,  0.5 + k}
        };
        res.min += block_offset();
        res.max += block_offset();
        return res;
    }

    void chunk::build_mesh() {
        m_mesh.clear();

        for (auto [i, j, k] : indices_of(m_data)) {
            if (m_data[i][j][k] == block::empty) {
                continue;
            }

            auto add_face = [&, this](face f) {
                m_mesh.add_indices(indices, m_mesh.vertices().size());
                m_mesh.add_vertices(vertices_of.at(f), [&](vertex v) {
                    v.position += glm::vec3{i, j, k};
                    ja::block block = m_data[i][j][k];
                    v.texcoord.z = texture_indices[block][static_cast<int>(f)];
                    return v;
                });
            };

            for (ja::face face : faces) {
                auto adjacent_pos = pos(i, j, k) + normal_of[face];
                if (auto block = m_terrain.block_at(adjacent_pos); block && is_transparant(block.value())) {
                    add_face(face);
                }
            }
        }

        m_mesh.build();
    }

    const mesh& chunk::mesh() const {
        return m_mesh;
    }

    glm::ivec3 chunk::id() const {
        return m_id;
    }

    void chunk::set_id(int i, int j, int k) {
        m_id.x = i;
        m_id.y = j;
        m_id.z = k;
    }

}
