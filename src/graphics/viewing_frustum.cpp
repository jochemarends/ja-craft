/**
 * @file viewing_frustum.cpp
 * @author Jochem Arends
 * @date 28-02-2024
 */

#include <graphics/viewing_frustum.h>
#include <glm/gtc/matrix_transform.hpp>

namespace ja {
    glm::mat4 viewing_frustum::proj() const {
        return glm::perspective(fov.radians(), aspect_ratio, near, far);
    }
}

