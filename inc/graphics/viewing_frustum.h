#ifndef VIEWING_FRUSTUM_H
#define VIEWING_FRUSTUM_H

#include <utility/angle.h>
#include <world/pose.h>

namespace ja {
    /**
     * Represents a viewing frustum.
     */
    struct viewing_frustum : pose {
        /*
         * Constructs a projection matrix of the viewing frustum.
         *
         * @return A projection matrix of the viewing frustum.
         */
        glm::mat4 proj() const;

        float aspect_ratio{};
        angle fov = 90.0_deg; /**< The field of view expressed in radians. */
        float near{};
        float far{};
    };
}

#endif

