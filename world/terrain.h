#ifndef JA_TERRAIN_H
#define JA_TERRAIN_H

#include "chunk.h"
#include "../gfx/program.h"

namespace ja {

    class terrain {
    public:
        static constexpr std::size_t render_distance = 2;
        static constexpr std::size_t width = render_distance * 2 + 1;
        static constexpr std::size_t depth = width;

        chunk(&chunks())[width][depth];
        const chunk(&chunks() const)[width][depth];

        terrain();
        void draw(const ja::program& program) const;
        chunk& chunk_at(const glm::vec3& pos);
        void update(const glm::vec3& pos);
        void center_to(const glm::vec3& pos);
        void center_to(int i, int j, int k);
        glm::vec3 m_position{};
        chunk m_chunks[width][depth];
        tuple_of_n<std::size_t, 2> pos_to_idx(glm::vec3 pos) const;
        tuple_of_n<int, 2> new_pos_to_idx(glm::vec3 pos);
        glm::vec3 idx_to_pos(std::size_t i, std::size_t j) const;
        int m_x, m_z;
    private:
    };

}

#endif
