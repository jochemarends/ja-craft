/**
 * @file buffer.cpp
 * @author Jochem Arends
 * @date 07-01-2024
 */

#include <graphics/buffer.h>

namespace ja::buffer {
    void deleter::operator()(GLuint buffer) {
        glDeleteBuffers(1, &buffer);
    }
    
    handle make() {
        GLuint buffer{};
        glGenBuffers(1, &buffer);
        return handle{buffer};
    }
}

