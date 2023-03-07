#ifndef JA_PROGRAM_H
#define JA_PROGRAM_H

#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ja {
    class program {
    public:
        program(const shader& vert, const shader& frag);
       ~program();
        program(const program& other) = delete;
        program& operator=(const program& other) = delete;
        void use() const;
        GLuint uniform_location(const std::string& name) const;
        [[nodiscard]] GLuint handle() const;
        [[nodiscard]] bool good() const;
        [[nodiscard]] std::string info_log() const;
    private:
        bool m_good;
        GLuint m_handle;
    };
}

#endif
