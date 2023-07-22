#ifndef JA_TERRAIN_H
#define JA_TERRAIN_H

#include "chunk.h"
#include "../gfx/program.h"
#include <unordered_map>

#define GLM_ENABLE_EXERIMENTAL
#include "glm/gtx/hash.hpp"

namespace ja {

    class terrain {
    public:
        static constexpr int range = 4;

        terrain();

        void draw(const ja::program& program) const;

        const std::ranges::view auto chunks() const;
        std::ranges::view auto chunks();

        glm::ivec3 pos_to_chunk_id(glm::vec3 pos) const;
        const chunk& chunk_at(glm::vec3 pos) const;
        chunk& chunk_at(glm::vec3 pos);

        block block_at(int i, int j, int k) const;

        void center_to(const glm::vec3& pos);
    private:
        glm::ivec3 min_chunk_id() const;
        glm::ivec3 max_chunk_id() const;

        glm::ivec3 m_center_chunk_id;
        std::unordered_map<glm::ivec3, chunk> m_chunks{};
    };



}

#endif
