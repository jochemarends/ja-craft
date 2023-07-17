#ifndef JA_TERRAIN_H
#define JA_TERRAIN_H

#include "chunk.h"
#include "../gfx/program.h"

namespace ja {

    class terrain {
    public:
        terrain();
        void draw(const ja::program& program) const;
        chunk& chunk_at(const glm::vec3& pos);
        void update(const glm::vec3& pos);
        void center_to(const glm::vec3& pos);
        glm::vec3 m_position{};
        chunk m_chunks[3][3];
        tuple_of_n<std::size_t, 2> pos_to_idx(glm::vec3 pos) const;
        tuple_of_n<int, 2> new_pos_to_idx(glm::vec3 pos);
        glm::vec3 idx_to_pos(std::size_t i, std::size_t j) const;
    private:
    };

}

#endif
