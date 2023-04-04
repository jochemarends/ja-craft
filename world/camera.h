#ifndef JA_CAMERA_H
#define JA_CAMERA_H

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace ja {
    class camera {
    public:
        camera(float near, float far, float aspect);
        glm::mat4 proj() const;
        glm::mat4 view() const;
        void move(glm::vec3 offset);
        void rotate(float pitch, float yaw, float roll);
        glm::vec3 m_position;
        glm::vec3 m_front;
    private:
        // position and orientation data
        glm::vec3 m_rotation;
        glm::vec3 m_up;

        // viewing fustrum data
        float m_near;
        float m_far;
        float m_aspect;
        float m_fov;
    };
}

#endif
