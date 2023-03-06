#include "camera.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

namespace ja {
    camera::camera(float near, float far, float aspect)
        :m_near{near}, m_far{far}, m_aspect{aspect}, m_fov{45.0f},
         m_front    {0.0f,  0.0f, -1.0f},
         m_up       {0.0f,  1.0f,  0.0f},
         m_position {0.0f,  0.0f,  2.0f},
         m_rotation {0.0f, -90.0f, 0.0f} {}

    glm::mat4 camera::proj() const {
        return glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
    }

    glm::mat4 camera::view() const {
        return glm::lookAt(m_position, m_position + m_front, m_up);
    }

    void camera::move(glm::vec3 offset) {
        m_position += offset.x * glm::normalize(glm::cross(m_up, m_front));
        m_position += offset.z * m_front;
        m_position += offset.y * m_up;
    }

    void camera::rotate(float pitch, float yaw, float roll) {
        m_rotation += glm::vec3{pitch, yaw, roll};
        m_front.x = std::cos(glm::radians(m_rotation.y)) * std::cos(glm::radians(m_rotation.x));
        m_front.y = std::sin(glm::radians(m_rotation.x));
        m_front.z = std::sin(glm::radians(m_rotation.y)) * std::cos(glm::radians(m_rotation.x));

        glm::vec3 upright{0.0f, 1.0f, 0.0f};
        glm::vec3 right = glm::normalize(glm::cross(upright, m_front));
        m_up = glm::cross(m_front, right);
    }
}