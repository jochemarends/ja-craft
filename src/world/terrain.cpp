#include <iostream>
#include "terrain.h"
#include "../gfx/program.h"
#include "../../PerlinNoise.h"
#include <ranges>
#include <thread>

namespace ja {



    terrain::terrain() {
        center_to(glm::ivec3{0, 0, 0});
        load_chunks();
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
            std::floor((pos.x + 0.5f) / chunk::width),
            0,
            std::floor((pos.z + 0.5f) / chunk::depth)
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

    optional_ref<const block> terrain::block_at(glm::vec3 pos) const {
        if (auto chunk = chunk_at(pos)) {
            glm::ivec3 idx = pos_to_chunk_idx(pos);
            return chunk->data()[idx.x][idx.y][idx.z];
        }
        return std::nullopt;
    }

    optional_ref<block> terrain::block_at(glm::vec3 pos) {
        if (auto chunk = chunk_at(pos)) {
            glm::ivec3 idx = pos_to_chunk_idx(pos);
            return chunk->data()[idx.x][idx.y][idx.z];
        }
        return std::nullopt;
    }

    std::optional<const block_info<const chunk>> terrain::get_block_info(glm::vec3 pos) const {
        if (auto chunk = chunk_at(pos)) {
            glm::ivec3 idx = pos_to_chunk_idx(pos);
            return block_info(*chunk, idx);
        }
        return std::nullopt;
    }

    glm::ivec3 terrain::min_chunk_id() const {
        return m_center_chunk_id - range;
    }

    glm::ivec3 terrain::max_chunk_id() const {
        return m_center_chunk_id + range;
    }

    glm::ivec3 terrain::pos_to_chunk_idx(glm::vec3 pos) const {
        // (a % b + b) % b is quite expensive. could use a & (b - 1) when b is a power of two!
        return glm::ivec3 {
            (static_cast<int>(pos.x) % chunk::width + chunk::width) % chunk::width,
            (static_cast<int>(pos.y) % chunk::height + chunk::height) % chunk::height,
            (static_cast<int>(pos.z) % chunk::depth + chunk::depth) % chunk::depth
        };
    }

    void terrain::center_to(const glm::vec3& pos) {
        if (m_center_chunk_id != std::exchange(m_center_chunk_id, pos_to_chunk_id(pos))) {
            unload_chunks();
            load_chunks();
        };
    }

    void terrain::unload_chunks() {
        ja::aabb aabb{
            .min = min_chunk_id(),
            .max = max_chunk_id()
        };

        std::erase_if(m_chunks, [&aabb](const auto& entry) {
            return !test(entry.first, aabb);
        });
    }

    void terrain::load_chunks() {
        for (int i = min_chunk_id().x; i <= max_chunk_id().x; ++i) {
            for (int j = min_chunk_id().z; j <= max_chunk_id().z; ++j) {
                glm::ivec3 id{i, 0, j};
                if (!m_chunks.contains(id)) {
                    m_chunks.emplace(id, *this);
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