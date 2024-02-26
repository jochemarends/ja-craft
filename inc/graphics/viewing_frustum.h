#ifndef VIEWING_FRUSTUM_H
#define VIEWING_FRUSTUM_H

#include <utility/angle.h>
#include <world/pose.h>

namespace ja {
    /**
     * Represents a viewing frustum.
     */
    struct viewing_frustum : pose {
        glm::mat4 proj() const;

        // pose pose{}; /**< The frustum's position and orientation. */
        double aspect_ratio;
        angle fov = 0.0_deg; /**< The field of view expressed in radians. */
        double near{};
        double far{};
    };
}

#endif

