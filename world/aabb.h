#ifndef JA_CRAFT_AABB_H
#define JA_CRAFT_AABB_H

#include <glm/glm.hpp>
#include <optional>
#include "mesh.h"

namespace ja {
    struct aabb {
        glm::vec3 min;
        glm::vec3 max;
    };

    struct ray {
        glm::vec3 origin;
        glm::vec3 direction;
    };

    bool test(const ja::aabb& a, const ja::aabb& b);
    std::optional<ja::face> test(const ja::ray& ray, const ja::aabb& aabb);
}

#endif
