#include <world/pose.h>
#include <glm/gtc/matrix_transform.hpp>

namespace ja {
    glm::mat4 pose::view() const {
        return glm::lookAt(position, position + front, up);
    }
}

