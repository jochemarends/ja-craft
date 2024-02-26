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
     * Represents a position and orientation in 3D space.
     */
    struct pose {
        /*
         * Constructs a view matrix for a pose.
         *
         * @return The view matrix for the pose.
         */
        glm::mat4 view() const;

        glm::vec3 position{0.0f, 0.0f,  0.0f};
        glm::vec3 front   {0.0f, 0.0f, -1.0f};
        glm::vec3 up      {0.0f, 1.0f,  0.0f};
    };
}

#endif

