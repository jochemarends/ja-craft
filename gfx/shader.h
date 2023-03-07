#ifndef JA_SHADER_H
#define JA_SHADER_H

#include <glad/glad.h>
#include <string_view>

namespace ja {
    class shader {
    public:
        enum class type {
            vert = GL_VERTEX_SHADER,
            frag = GL_FRAGMENT_SHADER,
            geom = GL_GEOMETRY_SHADER
        };
        shader(shader::type type, std::string_view filename);
        ~shader();
        shader(const shader& other) = delete;
        shader& operator=(const shader& other) = delete;
        [[nodiscard]] GLuint handle() const;
        [[nodiscard]] bool good() const;
        [[nodiscard]] std::string info_log() const;
    private:
        bool m_good;
        GLuint m_handle;
    };
}

#endif