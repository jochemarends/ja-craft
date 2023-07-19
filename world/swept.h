#ifndef JA_SWEPT_H
#define JA_SWEPT_H

#include "aabb.h"
#include "chunk.h"
#include "terrain.h"

namespace ja {

    struct swept_result {
        float time;
        glm::vec3 normal;
    };

    swept_result swept(const ja::aabb& a, const ja::aabb& b, glm::vec3 velocity);
    swept_result swept(const aabb& a, const chunk& chunk, glm::vec3 velocity);
    swept_result swept(const aabb& a, const terrain& terrain, glm::vec3 velocity);

}

#endif
