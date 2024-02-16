/**
 * @file vertex_array.cpp
 * @author Jochem Arends
 * @date 07-01-2024
 */

#include <graphics/vertex_array.h>

namespace ja::vertex_array {
    void deleter::operator()(GLuint vao) {
        glDeleteVertexArrays(1, &vao);
    }

    handle make() {
        GLuint vao{};
        glGenVertexArrays(1, &vao);
        return handle{vao};
    }
}

