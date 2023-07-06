#ifndef JA_CRAFT_AABB_H
#define JA_CRAFT_AABB_H

#include <glm/glm.hpp>
#include <optional>
#include "mesh.h"

namespace ja {
    struct aabb {
        float width() const;
        float height() const;
        float depth() const;
        glm::vec3 min;
        glm::vec3 max;
    };

    struct ray {
        glm::vec3 origin;
        glm::vec3 direction;
    };

    struct swept_result {
        float time;
        glm::vec3 normal;
    };

    bool test(const ja::aabb& a, const ja::aabb& b);
    std::optional<ja::face> test(const ja::ray& ray, const ja::aabb& aabb);
    swept_result swept(const ja::aabb& a, const ja::aabb& b, glm::vec3 velocity);
}

#endif
