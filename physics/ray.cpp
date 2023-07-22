#include "ray.h"
#include <functional>

namespace ja {

    std::optional<ja::face> test(const ja::ray& ray, const ja::aabb& aabb) {
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

    std::optional<ray::chunk_hit_info> test(const ray& ray, const chunk& chunk) {
        std::optional<ray::chunk_hit_info> res{};

        for (auto [i, j, k] : indices_of(chunk.data())) {
            if (chunk.data()[i][j][k] == block::empty) continue;

            if (auto hit = test(ray, chunk.aabb(i, j, k))) {
                auto get_pos = [&chunk](auto ii, auto jj, auto kk) {
                    return chunk.pos(ii, jj, kk);
                };

                float d1 = std::numeric_limits<float>::infinity();
                if (res.has_value()) {
                    d1 = glm::distance(ray.origin, std::apply(get_pos, res->index));
                }

                auto d2 = glm::distance(ray.origin, get_pos(i, j, k));

                if (d2 < d1) {
                    res = {{i, j, k}, hit.value()};
                }
            }
        }

        return res;
    }

    std::optional<ray::terrain_hit_info> test(const ray& ray, const terrain& terrain) {
        std::optional<ray::terrain_hit_info> res{};

        for (const ja::chunk& chunk : terrain.chunks()) {
            if (!test(ray, chunk.aabb()) && !test(ray.origin, chunk.aabb())) continue;

            if (auto hit = test(ray, chunk)) {
                auto get_pos = [&](const ja::chunk& chunk, auto i, auto j, auto k) {
                    return chunk.pos(i, j, k);
                };

                auto get_pos_a = std::bind_front(get_pos, res->chunk);
                auto get_pos_b = std::bind_front(get_pos, std::ref(chunk));

                float d1 = std::numeric_limits<float>::infinity();
                if (res.has_value()) {
                    d1 = glm::distance(ray.origin, std::apply(get_pos_a, res->index));
                }

                auto d2 = glm::distance(ray.origin, std::apply(get_pos_b, hit->index));

                if (d2 < d1) {
                    res = {const_cast<ja::chunk&>(chunk), hit->index, hit->face};
                }
            }
        }

        return res;
    }

}