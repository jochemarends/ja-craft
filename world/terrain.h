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
        static constexpr int width =  16;
        static constexpr int height = 16;
        static constexpr int depth =  16;

        static constexpr int range = 4;

        terrain();

//        chunk(&chunks())[width][depth];
//        const chunk(&chunks() const)[width][depth];

        const std::optional<chunk&> chunk_at(int i, int j, int k) const;
        chunk& chunk_at(int i, int j, int k);
        const chunk& chunk_at(const glm::vec3& pos) const;
        chunk& chunk_at(const glm::vec3& pos);

        block block_at(int i, int j, int k) const;


        void draw(const ja::program& program) const;
        void update(const glm::vec3& pos);

        void center_to(const glm::vec3& pos);
        void center_to(int i, int j, int k);
        glm::vec3 m_position{};
        glm::ivec3 pos_to_chunk_id(glm::vec3 pos) const;
        tuple_of_n<int, 2> new_pos_to_idx(glm::vec3 pos);
        glm::vec3 idx_to_pos(std::size_t i, std::size_t j) const;
    private:
        glm::ivec3 min_id() const;
        glm::ivec3 max_id() const;

        glm::ivec3 m_center_id;
        std::unordered_map<glm::ivec3, chunk> m_chunks{};
    };

}

#endif
