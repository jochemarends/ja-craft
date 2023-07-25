#ifndef JA_CAMERA_H
#define JA_CAMERA_H

#include <glm/glm.hpp>
#include "glad/glad.h"
#include "../physics/aabb.h"

namespace ja {
    class camera {
    public:
        camera(float near, float far, float aspect);
        glm::mat4 proj() const;
        glm::mat4 view() const;
        void move(glm::vec3 offset);
        void aarg(glm::vec3 offset);
        void rotate(float pitch, float yaw, float roll);

        ja::aabb aabb() const {
            return ja::aabb{
                .min{glm::vec3{-0.4f, -0.4f, -0.4f} + m_position},
                .max{glm::vec3{ 0.4f,  0.4f,  0.4f} + m_position}
            };
        }

        glm::vec3 m_position;
        glm::vec3 m_front;
        // pos and orientation data
        glm::vec3 m_rotation;
        glm::vec3 m_up;

        // viewing fustrum data
        float m_near;
        float m_far;
        float m_aspect;
        float m_fov;
    private:
    };
}

#endif
