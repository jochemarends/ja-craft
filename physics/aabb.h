#ifndef JA_CRAFT_AABB_H
#define JA_CRAFT_AABB_H

#include <glm/glm.hpp>
#include <optional>
#include "../gfx/mesh.h"

namespace ja {

    struct aabb {
        float width() const;
        float height() const;
        float depth() const;
        glm::vec3 min;
        glm::vec3 max;
    };

    bool test(const ja::aabb& a, const ja::aabb& b);
    bool test(glm::vec3 a, const ja::aabb& b);

}

#endif
