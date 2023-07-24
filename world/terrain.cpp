#include <iostream>
#include "terrain.h"
#include "../gfx/program.h"
#include "../PerlinNoise.h"
#include <ranges>

namespace ja {

    terrain::terrain() {
        center_to(glm::ivec3{0, 0, 0});
    }

    void terrain::draw(const ja::program& program) const {
        for (const ja::chunk& chunk : m_chunks | std::views::values) {
            glm::mat4 model{1};
            model = glm::translate(model, chunk.pos());
            glUniformMatrix4fv(program.uniform_location("model"), 1, GL_FALSE, glm::value_ptr(model));
            chunk.mesh().draw();
        }
    }

    glm::ivec3 terrain::pos_to_chunk_id(glm::vec3 pos) const {
        return glm::ivec3{
            std::floor(pos.x / chunk::width),
            0,
            std::floor(pos.z / chunk::depth)
        };
    }

    optional_ref<const chunk> terrain::chunk_at(glm::vec3 pos) const {
        if (auto it = m_chunks.find(pos_to_chunk_id(pos)); it != m_chunks.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    optional_ref<chunk> terrain::chunk_at(glm::vec3 pos) {
        if (auto it = m_chunks.find(pos_to_chunk_id(pos)); it != m_chunks.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    glm::ivec3 terrain::min_chunk_id() const {
        return m_center_chunk_id - range;
    }

    glm::ivec3 terrain::max_chunk_id() const {
        return m_center_chunk_id + range;
    }

    optional_ref<block> terrain::block_at(int x, int y, int z) {
        if (auto chunk = chunk_at(glm::vec3{x, y, z})) {
            int i = ((x % chunk::width) + chunk::width) % chunk::width;
            int j = ((y % chunk::height) + chunk::height) % chunk::height;
            int k = ((z % chunk::depth) + chunk::depth) % chunk::depth;
            return const_cast<block&>(chunk->data()[i][j][k]);
        }
        return std::nullopt;
    }

    void terrain::center_to(const glm::vec3& pos) {
        if (m_center_chunk_id == std::exchange(m_center_chunk_id, pos_to_chunk_id(pos))) {
            return; // terrain is already up to date
        };

        for (int i = min_chunk_id().x; i < max_chunk_id().x; ++i) {
            for (int j = min_chunk_id().z; j < max_chunk_id().z; ++j) {
                glm::ivec3 id{i, 0, j};

                if (!m_chunks.contains(id)) {
                    m_chunks.insert({id, chunk{*this}});
                    m_chunks.at(id).set_id(i, 0, j);
                }
            }
        }

        for (ja::chunk& chunk : m_chunks | std::views::values) {
            m_generator.generate(chunk);
            chunk.build_mesh();
        }
    }

}