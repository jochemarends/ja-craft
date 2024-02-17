/**
 * @file pose.h
 * @author Jochem Arends
 * @date 17-02-2024
 */

#ifndef POSE_H
#define POSE_H

#include <glm/glm.hpp>

namespace ja {
    /**
     * A 3D pose.
     *
     * Represent a position and orientation in 3D space.
     */
    struct pose {
        glm::vec3 position{};
        glm::vec3 front{};
        glm::vec3 up{};
    };
}

#endif

