#include <graphics/mesh.h>

namespace ja {
    void mesh::bind() const {
        glBindVertexArray(m_vao.get());
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo.get());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo.get());
    }

    mesh::mesh() {
        glBindVertexArray(m_vao.get());
        // add the position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(offsetof(vertex, m_position)));
        glEnableVertexAttribArray(0);
        // add the texture coordinate attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(offsetof(vertex, m_texcoord)));
        glEnableVertexAttribArray(1);
    }
}

