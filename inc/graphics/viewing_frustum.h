#ifndef VIEWING_FRUSTUM_H
#define VIEWING_FRUSTUM_H

#include <world/pose.h>

namespace ja {
    /**
     * Represents a viewing frustum.
     */
    struct viewing_frustum {
        pose pose{}; /**< The frustum's position and orientation. */
        double aspect_ratio{};
        double fov_rad{}; /**< The field of view expressed in radians. */
        double near{};
        double far{};
    };
}

#endif

