#ifndef JA_RAY
#define JA_RAY

#include "aabb.h"
#include "chunk.h"
#include "terrain.h"
#include "../util/indices_view.h"

namespace ja {

    struct ray {
        struct chunk_hit_info;
        struct terrain_hit_info;
        glm::vec3 origin;
        glm::vec3 direction;
    };

    struct ray::chunk_hit_info {
        tuple_of_n<std::size_t, 3> index;
        ja::face face;
    };

    struct ray::terrain_hit_info {
        std::reference_wrapper<ja::chunk> chunk;
        tuple_of_n<std::size_t, 3> index;
        ja::face face;
    };

    std::optional<ja::face> test(const ja::ray& ray, const ja::aabb& aabb);
    std::optional<ray::chunk_hit_info> test(const ja::ray& ray, const ja::chunk& chunk);
    std::optional<ray::terrain_hit_info> test(const ja::ray& ray, const ja::terrain& terrain);

}

#endif
