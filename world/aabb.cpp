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
    float aabb::width() const {
        return std::abs(max.x - min.x);
    }

    float aabb::height() const {
        return std::abs(max.y - min.y);
    }

    float aabb::depth() const {
        return std::abs(max.z - min.z);
    }

    swept_result swept(const ja::aabb& a, const ja::aabb& b, glm::vec3 velocity) {
        glm::vec3 entry, exit;

        entry.x = b.min.x - (a.min.x + a.width());
        entry.y = b.min.y - (a.min.y + a.height());
        entry.z = b.min.z - (a.min.z + a.depth());

        exit.x = (b.min.x + b.width()) - a.min.x;
        exit.y = (b.min.y + b.height()) - a.min.y;
        exit.z = (b.min.z + b.depth()) - a.min.z;

        if (velocity.x <= 0.0f) std::swap(entry.x, exit.x);
        if (velocity.y <= 0.0f) std::swap(entry.y, exit.y);
        if (velocity.z <= 0.0f) std::swap(entry.z, exit.z);

        glm::vec3 entry_time{-std::numeric_limits<float>::infinity()};
        glm::vec3 exit_time{std::numeric_limits<float>::infinity()};

        if (velocity.x != 0.0f) {
            entry_time.x = entry.x / velocity.x;
            exit_time.x = exit.x / velocity.x;
        }

        if (velocity.y != 0.0f) {
            entry_time.y = entry.y / velocity.y;
            exit_time.y = exit.y / velocity.y;
        }

        if (velocity.z != 0.0f) {
            entry_time.z = entry.z / velocity.z;
            exit_time.z = exit.z / velocity.z;
        }

        float max_entry_time = std::max(entry_time.x, std::max(entry_time.y, entry_time.z));
        float min_exit_time = std::min(exit_time.x, std::min(exit_time.y, exit_time.z));
        float max_exit_time = std::max(exit_time.x, std::max(exit_time.y, exit_time.z));

        swept_result res{.time = max_entry_time, .normal{}};
        if (max_entry_time > min_exit_time || max_entry_time < 0.0f || max_entry_time > 1.0f) {
            res.time = 1.0f;
            return res;
        }

        if (entry_time.x == max_entry_time) {
            res.normal.x = (entry.x < 0.0f) ? 1.0f : -1.0f;
            res.normal.y = res.normal.z = 0.0f;
        }

        if (entry_time.y == max_entry_time) {
            res.normal.y = (entry.y < 0.0f) ? 1.0f : -1.0f;
            res.normal.x = res.normal.z = 0.0f;
        }

        if (entry_time.z == max_entry_time) {
            std::cout << "entry.z: " << entry.z << '\n';
            res.normal.z = (entry.z < 0.0f) ? 1.0f : -1.0f;
            res.normal.x = res.normal.y = 0.0f;
        }

        return res;
    }

    float swept_old(const ja::aabb& a, const ja::aabb& b, glm::vec3 velocity) {
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