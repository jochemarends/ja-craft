#ifndef JA_TERRAIN_H
#define JA_TERRAIN_H

#include "chunk.h"

namespace ja {

    class terrain {
    public:
        terrain();
        void draw() const;
        const chunk& chunk_at(const glm::vec3& pos);
        void update(const glm::vec3& pos);
        glm::vec3 m_position;
        chunk m_chunks[3][3];
    private:
    };

}

#endif
