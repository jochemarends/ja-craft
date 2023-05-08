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
            if (t1s[i] == tmin) return faces[i].second;
            if (t2s[i] == tmin) return faces[i].first;
        }
    }

    return std::nullopt;
}

namespace ja {

    float swept(const ja::aabb& a, const ja::aabb& b, glm::vec3 velocity) {
        // step 1: calculate distances
        glm::vec3 entry_point, exit_point;

        float a_width = std::abs(a.max.x - a.min.x);
        float b_width = std::abs(b.max.x - b.min.x);
        entry_point.x = b.min.x - (a.min.x + a_width);
        exit_point.x  = (b.min.x + b_width) - a.min.x;
        if (velocity.x <= 0.0f) std::swap(entry_point.x, exit_point.x);

        float a_height = std::abs(a.max.y - a.min.y);
        float b_height = std::abs(b.max.y - b.min.y);
        entry_point.y = b.min.y - (a.min.y + a_height);
        exit_point.y  = (b.min.y + b_height) - a.min.y;
        if (velocity.y <= 0.0f) std::swap(entry_point.y, exit_point.y);

        float a_depth = std::abs(a.max.z - a.min.z);
        float b_depth = std::abs(b.max.z - b.min.z);
        entry_point.z = b.min.z - (a.min.z + a_depth);
        exit_point.z  = (b.min.z + b_depth) - a.min.z;
        if (velocity.z <= 0.0f) std::swap(entry_point.z, exit_point.z);

        // step 2: calculate times
        glm::vec3 entry_times {
            -std::numeric_limits<float>::infinity(),
            -std::numeric_limits<float>::infinity(),
            -std::numeric_limits<float>::infinity()
        };

        glm::vec3 exit_times {
             std::numeric_limits<float>::infinity(),
             std::numeric_limits<float>::infinity(),
             std::numeric_limits<float>::infinity()
        };

        if (velocity.x != 0.0f) {
            entry_times.x = entry_point.x / velocity.x;
            exit_times.x = exit_point.x / velocity.x;
        }

        if (velocity.y != 0.0f) {
            entry_times.y = entry_point.y / velocity.y;
            exit_times.y = exit_point.y / velocity.y;
        }

        if (velocity.z != 0.0f) {
            entry_times.z = entry_point.z / velocity.z;
            exit_times.z = exit_point.z / velocity.z;
        }

        float entry_time = std::max(entry_times.x, std::max(entry_times.y, entry_times.z));
        float exit_time = std::min(exit_times.x, std::min(exit_times.y, exit_times.z));

        if (entry_time > exit_time || entry_times.x < 0.0f && entry_times.y < 0.0f && entry_times.z < 0.0f || entry_times.x > 1.0f || entry_times.y > 1.0f || entry_times.z > 1.0f) {
            return 1.0f;
        }

        return entry_time;
    }

}