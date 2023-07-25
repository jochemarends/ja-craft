#include "aabb.h"
#include <iostream>

namespace ja {

    bool test(const ja::aabb& a, const ja::aabb& b) {
        return a.min.x <= b.max.x &&
               a.max.x >= b.min.x &&
               a.min.y <= b.max.y &&
               a.max.y >= b.min.y &&
               a.min.z <= b.max.z &&
               a.max.z >= b.min.z;
    }

    bool test(glm::vec3 a, const ja::aabb& b) {
        return a.x >= b.min.x &&
               a.x <= b.max.x &&
               a.y >= b.min.y &&
               a.y <= b.max.y;
    }

    float aabb::width() const {
        return std::abs(max.x - min.x);
    }

    float aabb::height() const {
        return std::abs(max.y - min.y);
    }

    float aabb::depth() const {
        return std::abs(max.z - min.z);
    }

    glm::vec3 aabb::center() const {
        return glm::vec3{
            min.x + width()  / 2.0f,
            min.y + height() / 2.0f,
            min.z + depth()  / 2.0f
        };
    }

}