#ifndef JA_TERRAIN_H
#define JA_TERRAIN_H

#include "chunk.h"
#include "flat_terrain_generator.h"
#include "default_terrain_generator.h"
#include "../gfx/program.h"
#include "../util/optional_ref.h"
#include <unordered_map>

#define GLM_ENABLE_EXERIMENTAL
#include "glm/gtx/hash.hpp"

namespace ja {

    struct block_info {
        const ja::block& value() const;
        std::reference_wrapper<const ja::chunk> chunk;
        glm::ivec3 index;
    };

    class terrain {
    public:
        static constexpr int range = 1;

        terrain();

        void draw(const ja::program& program) const;

        const auto chunks() const {
            return m_chunks | std::views::values;
        };

        auto chunks() {
            return m_chunks | std::views::values;
        }

        glm::ivec3 pos_to_chunk_id(glm::vec3 pos) const;
        glm::ivec3 pos_to_chunk_idx(glm::vec3 pos) const;

        optional_ref<const chunk> chunk_at(glm::vec3 pos) const;
        optional_ref<chunk> chunk_at(glm::vec3 pos);

        optional_ref<const block> block_at(glm::vec3 pos) const;
        optional_ref<block> block_at(glm::vec3 pos);

        std::optional<const block_info> get_block(glm::vec3 pos) const;

        optional_ref<block> block_at(int x, int y, int z);

        void center_to(const glm::vec3& pos);
    private:
        glm::ivec3 min_chunk_id() const;
        glm::ivec3 max_chunk_id() const;
        void unload_chunks();
        void load_chunks();

        glm::ivec3 m_center_chunk_id;
        std::unordered_map<glm::ivec3, chunk> m_chunks{};
        default_terrain_generator m_generator;
    };

}

#endif
