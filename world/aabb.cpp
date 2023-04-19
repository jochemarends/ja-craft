#include "aabb.h"
#include <iostream>

bool ja::test(const ja::aabb &a, const ja::aabb &b) {
    return a.min.x <= b.max.x &&
           a.max.x >= b.min.x &&
           a.min.y <= b.max.y &&
           a.max.y >= b.min.y &&
           a.min.z <= b.max.z &&
           a.max.z >= b.min.z;
}

std::optional<ja::face> ja::test(const ja::ray& ray, const ja::aabb& aabb) {
    float tmin = 0.0f;
    float tmax = std::numeric_limits<float>::infinity();

    float t1s[3], t2s[3];
    for (int i{0}; i < 3; ++i) {
        if (ray.direction[i] != 0.0f) {
            t1s[i] = (aabb.min[i] - ray.origin[i]) / ray.direction[i];
            t2s[i] = (aabb.max[i] - ray.origin[i]) / ray.direction[i];
            tmin = std::max(tmin, std::min(t1s[i], t2s[i]));
            tmax = std::min(tmax, std::max(t1s[i], t2s[i]));
        }
        else if (ray.origin[i] <= aabb.min[i] || ray.origin[i] >= aabb.max[i]) {
            return std::nullopt;
        }
    }

    if (tmax >= tmin) {
        static const std::pair<face, face> faces[]{
            {face::left,  face::right},
            {face::top,   face::bottom},
            {face::front, face::back}
        };

        for (int i{0}; i < 3; ++i) {
            if (t1s[i] == tmin) return faces[i].first;
            if (t2s[i] == tmin) return faces[i].second;
        }
    }

    return std::nullopt;
}