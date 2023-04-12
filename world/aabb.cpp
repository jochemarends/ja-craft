#include "aabb.h"

bool ja::test(const ja::aabb &a, const ja::aabb &b) {
    return a.min.x <= b.max.x &&
           a.max.x >= b.min.x &&
           a.min.y <= b.max.y &&
           a.max.y >= b.min.y &&
           a.min.z <= b.max.z &&
           a.max.z >= b.min.z;
}

std::optional<ja::face> ja::test(const ja::ray& ray, const ja::aabb& aabb) {
    float tmin = -std::numeric_limits<float>::infinity();
    float tmax =  std::numeric_limits<float>::infinity();

    if (glm::dot(aabb.min - ray.origin, ray.direction) < 0) return std::nullopt;

    float buffer[3];

    for (int i = 0; i < 3; ++i) {
        if (ray.direction[i] != 0.0f) {
            float t1 = (aabb.min[i] - ray.origin[i]) / ray.direction[i];
            float t2 = (aabb.max[i] - ray.origin[i]) / ray.direction[i];

            tmin = std::max(tmin, buffer[i] = std::min(t1, t2));
            tmax = std::min(tmax, std::max(t1, t2));
        }
        else if (ray.origin[i] <= aabb.min[i] || ray.origin[i] >= aabb.max[i]) {
            return std::nullopt;
        }
    }

    return ja::face::left;
    // tmax >= tmin;
}
