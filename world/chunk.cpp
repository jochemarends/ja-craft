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
        for (auto [i, j, k] : indices_of(m_data)) {
            if (i == 0 && j == 0 && k == 0) continue;
            m_data[i][j][k] = block::empty;
        }
    }

    block(&chunk::data())[width][height][depth] {
        return m_data;
    }

    const block(&chunk::data() const)[width][height][depth] {
        return m_data;
    }

    glm::vec3 chunk::pos() const {
        return glm::vec3{
            m_id.x * width,
            m_id.y * height,
            m_id.z * depth
        };
    }

    glm::vec3 chunk::pos(std::size_t i, std::size_t j, std::size_t k) const {
        return glm::vec3{i, j, k} + pos();
    }

    ja::aabb chunk::aabb() const {
        ja::aabb res{
            .min{-0.5f,                 -0.5f,        -0.5f},
            .max{ width - 0.5f, height - 0.5f, depth - 0.5f}
        };
        res.min += pos();
        res.max += pos();
        return res;
    }

    ja::aabb chunk::aabb(std::size_t i, std::size_t j, std::size_t k) const {
        ja::aabb res{
            .min{-0.5 + i, -0.5 + j, -0.5 + k},
            .max{ 0.5 + i,  0.5 + j,  0.5 + k}
        };
        res.min += pos();
        res.max += pos();
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
                auto v = pos(i, j, k) + normal_of[face];
                if (auto block = m_terrain.block_at(v.x, v.y, v.z); block && is_transparant(block.value())) {
                    add_face(face);
                }
            }

            continue;
            // front face
            if (k + 1 < depth && is_transparant(m_data[i][j][k + 1])) {
                add_face(face::front);
            }

            // back face
            if (k - 1 >= 0 && is_transparant(m_data[i][j][k - 1])) {
                add_face(face::back);
            }

            // left face
            if (i - 1 >= 0 && is_transparant(m_data[i - 1][j][k])) {
                add_face(face::left);
            }

            // right face
            if (i + 1 < width && is_transparant(m_data[i + 1][j][k])) {
                add_face(face::right);
            }

            // top face
            if (j + 1 < height && is_transparant(m_data[i][j + 1][k])) {
                add_face(face::top);
            }

            // bottom face
            if (j - 1 >= 0 && is_transparant(m_data[i][j - 1][k])) {
                add_face(face::bottom);
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
