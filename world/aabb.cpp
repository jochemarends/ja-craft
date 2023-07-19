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

    float aabb::width() const {
        return std::abs(max.x - min.x);
    }

    float aabb::height() const {
        return std::abs(max.y - min.y);
    }

    float aabb::depth() const {
        return std::abs(max.z - min.z);
    }

}