/**
 * @file pose.cpp
 * @author Jochem Arends
 * @date 17-02-2024
 */

#include <world/pose.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace ja {
    glm::mat4 pose::view() const {
        return glm::lookAt(position, position + front, up);
    }

    void pose::move(glm::vec3 delta) {
        position += delta.x * glm::normalize(glm::cross(up, front));
        position += delta.y * up;
        position += delta.z * front;
    }

    void pose::rotate(angle pitch, angle heading, [[maybe_unused]] angle roll) {
        // applies the rotation to 3D vector
        auto apply = [&](glm::vec3& vec) {
            vec = glm::rotate(vec, pitch.radians(), glm::normalize(glm::cross(up, front)));
            glm::vec3 upright{0.0f, 1.0f, 0.0f};
            vec = glm::rotate(vec, heading.radians(), upright);
        };

        apply(front);
        apply(up);
    }
}

