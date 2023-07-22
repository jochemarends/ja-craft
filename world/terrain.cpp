#include <iostream>
#include "terrain.h"
#include "../gfx/program.h"
#include "../PerlinNoise.h"
#include <ranges>

namespace ja {

    terrain::terrain() {
        for (int i = min_chunk_id().x; i < max_chunk_id().x; ++i) {
            for (int j = min_chunk_id().z; j < max_chunk_id().z; ++j) {
                glm::ivec3 id{i, 0, j};
                m_chunks[id].set_id(i, 0, j);
            }
        }

        for (ja::chunk& chunk : m_chunks | std::views::values) {
            chunk.build_mesh();
        }
    }

    void terrain::draw(const ja::program& program) const {
        for (const ja::chunk& chunk : m_chunks | std::views::values) {
            glm::mat4 model{1};
            model = glm::translate(model, chunk.pos());
            glUniformMatrix4fv(program.uniform_location("model"), 1, GL_FALSE, glm::value_ptr(model));
            chunk.mesh().draw();
        }
    }

    std::ranges::view auto terrain::chunks() {
        return m_chunks | std::views::values;
    }

    const std::ranges::view auto terrain::chunks() const {
        return m_chunks | std::views::values;
    }

    glm::ivec3 terrain::pos_to_chunk_id(glm::vec3 pos) const {
        return glm::ivec3{
            std::floor(pos.x / chunk::width),
            std::floor(pos.y / chunk::height),
            std::floor(pos.z / chunk::depth)
        };
    }

    const chunk& terrain::chunk_at(glm::vec3 pos) const {
        return m_chunks.at(pos_to_chunk_id(pos));
    }

    chunk& terrain::chunk_at(glm::vec3 pos) {
        return m_chunks[pos_to_chunk_id(pos)];
    }

    glm::ivec3 terrain::min_chunk_id() const {
        return m_center_chunk_id - range;
    }

    glm::ivec3 terrain::max_chunk_id() const {
        return m_center_chunk_id + range;
    }

    void terrain::center_to(const glm::vec3& pos) {
        if (m_center_chunk_id == std::exchange(m_center_chunk_id, pos_to_chunk_id(pos))) {
            return; // terrain is already up to date
        };

        for (int i = min_chunk_id().x; i < max_chunk_id().x; ++i) {
            for (int j = min_chunk_id().z; j < max_chunk_id().z; ++j) {
                glm::ivec3 id{i, 0, j};
                m_chunks[id].set_id(i, 0, j);
            }
        }

        for (ja::chunk& chunk : m_chunks | std::views::values) {
            chunk.data()[0][0][0] = ja::grass; // for testing
            chunk.build_mesh();
        }
    }

}