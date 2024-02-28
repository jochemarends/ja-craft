/**
 * @file pose.cpp
 * @author Jochem Arends
 * @date 17-02-2024
 */

#include <world/pose.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace ja {
    glm::mat4 pose::view() const {
        return glm::lookAt(position, position + front, up);
    }

    void pose::move(glm::vec3 delta) {
        position += delta.x * glm::normalize(glm::cross(up, front));
        position += delta.y * up;
        position += delta.z * front;
    }

    void pose::rotate(angle pitch, angle heading, angle roll) {
        glm::quat rotation{glm::vec3{pitch.radians(), heading.radians(), roll.radians()}};
        auto mat{glm::mat3_cast(rotation)};
        front = mat * front;
        up = mat * up;
    }
}

