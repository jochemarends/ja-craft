/**
 * @file texture.cpp
 * @author Jochem Arends
 * @date 24-04-2024
 */

#include <graphics/texture.h>

namespace ja::texture {
    void deleter::operator()(GLuint texture) {
        glDeleteTextures(1, &texture);
    }

    handle make() {
        GLuint texture{};
        glGenTextures(1, &texture);
        return handle{texture};
    }
}
