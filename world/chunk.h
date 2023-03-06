#ifndef JA_CRAFT_CHUNK_H
#define JA_CRAFT_CHUNK_H

#include <glad/glad.h>

namespace ja {

    vertex_type
    class chunk {

        GLuint m_vbo, m_ebo, m_vao;
    };

    template<typename vertex_type>
    struct mesh {
        vertex_type
    };
}

#endif
