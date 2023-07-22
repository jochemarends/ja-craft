#include <iostream>
#include "terrain.h"
#include "../gfx/program.h"
#include "../PerlinNoise.h"
#include <ranges>

namespace ja {

//    chunk(&terrain::chunks())[terrain::width][terrain::depth] {
//        return m_chunks;
//    }
//
//    const chunk(&terrain::chunks() const)[terrain::width][terrain::depth] {
//        return m_chunks;
//    }

    glm::ivec3 terrain::min_id() const {
        return m_center_id - range;
    }

    glm::ivec3 terrain::max_id() const {
        return m_center_id + range;
    }

    terrain::terrain() {
        for (int i = min_id().x; i < max_id().x; ++i) {
            for (int j = min_id().z; j < max_id().z; ++j) {
                glm::ivec3 id{i, 0, j};
                m_chunks[id].set_id(i, 0, j);
            }
        }

        for (ja::chunk& chunk : m_chunks | std::views::values) {
            chunk.build_mesh();
        }
    }

    chunk& terrain::chunk_at(const glm::vec3& pos) {
        auto [i, j] = pos_to_chunk_id(pos);
        return m_chunks[i][j];
    }

    void terrain::draw(const ja::program& program) const {
        for (auto [i, j] : indices_of(m_chunks)) {
            glm::mat4 model{1};
            model = glm::translate(model, m_chunks[i][j].pos());
            glUniformMatrix4fv(program.uniform_location("model"), 1, GL_FALSE, glm::value_ptr(model));
            m_chunks[i][j].mesh().draw();
        }
    }

    glm::ivec3 terrain::pos_to_chunk_id(glm::vec3 pos) const {
        return {
            (pos.x - m_position.x) / chunk::width,
            (pos.z - m_position.z) / chunk::depth
        };
    }

    tuple_of_n<int, 2> terrain::new_pos_to_idx(glm::vec3 pos) {
            return {
                    (pos.x - m_position.x) / chunk::width,
                    (pos.z - m_position.z) / chunk::depth
            };
    }

    glm::vec3 terrain::idx_to_pos(std::size_t i, std::size_t j) const {
        return {i * chunk::width, 0, j * chunk::depth};
    }

    void terrain::center_to(const glm::vec3& pos) {
        int x = std::floor(pos.x / chunk::width);
        int z = std::floor(pos.z / chunk::depth);

        if (std::abs(x - m_x) > 1 || std::abs(z - m_z) > 1) {
            center_to(x, 0, z);
        }
    }

    void terrain::center_to(int i, int j, int k) {
        for (auto [ii, jj] : indices_of(m_chunks)) {
            auto x = (i + static_cast<int>(ii) - static_cast<int>(render_distance)) * chunk::width;
            auto z = (j + static_cast<int>(jj) - static_cast<int>(render_distance)) * chunk::depth;
            m_chunks[ii][jj].pos() = glm::vec3{x, 0.0f, z};
        }
        m_position = m_chunks[0][0].pos();
        m_x = i;
        m_z = k;
    }

}