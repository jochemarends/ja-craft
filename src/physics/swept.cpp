#include "swept.h"

namespace ja {

    bool swept_result::is_hit() const {
        return time < 1.0f;
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
            res.normal.z = (entry.z < 0.0f) ? 1.0f : -1.0f;
            res.normal.x = res.normal.y = 0.0f;
        }

        return res;
    }

    swept_result swept(const ja::aabb& a, const ja::chunk& chunk, glm::vec3 velocity) {
        swept_result res{1.0f, {}};
        for (auto [i, j, k] : indices_of(chunk.data())) {
            if (chunk.data()[i][j][k] == ja::block::empty) continue;
            if (glm::distance(chunk.pos(i, j, k), a.center()) > 2.0f)  continue;

            swept_result new_res = swept(a, chunk.aabb(i, j, k), velocity);

            if (new_res.time < res.time) {
                glm::vec adjacent_pos = chunk.pos(i, j, k) + new_res.normal;

                if (auto block = chunk.terrain().block_at(adjacent_pos)) {
                    if (*block == empty) res = new_res;
                }

            }
        }
        return res;
    }

    swept_result swept(const ja::aabb& a, const ja::terrain& terrain , glm::vec3 velocity) {
        glm::ivec3 step{
            (velocity.x < 0.0f) ? -1 : 1,
            (velocity.y < 0.0f) ? -1 : 1,
            (velocity.z < 0.0f) ? -1 : 1
        };

        glm::ivec3 pos = a.center();
        glm::ivec3 min = pos - 3;
        glm::ivec3 max = pos + 3;

        swept_result res{1.0f, {}};
        for (int i = min.x; i <= max.x; ++i) {
            for (int j = min.y; j <= max.y; ++j) {
                for (int k = min.z; k <= max.z; ++k) {
                    if (auto block_info = terrain.get_block_info({i, j, k})) {
                        if (block_info->value() == empty) continue;

                        swept_result new_res = swept(a, block_info->aabb(), velocity);
                        if (new_res.time < res.time) {
                            res = new_res;
                        }
                    }
                }
            }
        }
        return res;
    }

}