#include "aabb.h"

bool ja::test(const ja::ray& ray, const ja::aabb& aabb) {
    float tmin = -std::numeric_limits<float>::infinity();
    float tmax =  std::numeric_limits<float>::infinity();

    for (int i = 0; i < 3; ++i) {
        if (ray.direction[i] != 0.0f) {
            float t1 = (aabb.min[i] - ray.origin[i]) / ray.direction[i];
            float t2 = (aabb.max[i] - ray.origin[i]) / ray.direction[i];

            tmin = std::max(tmin, std::min(t1, t2));
            tmax = std::min(tmax, std::max(t1, t2));
        }
        else if (ray.origin[i] <= aabb.min[i] || ray.origin[i] >= aabb.max[i]) {
            return false;
        }
    }
    return tmax >= tmin;
}
