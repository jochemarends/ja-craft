#ifndef JA_CRAFT_AABB_H
#define JA_CRAFT_AABB_H

#include <glm/glm.hpp>

namespace ja {
    struct aabb {
        glm::vec3 min;
        glm::vec3 max;
    };

    struct ray {
        glm::vec3 origin;
        glm::vec3 direction;
    };

    bool test(const ja::ray& ray, const ja::aabb& aabb);
}

#endif
