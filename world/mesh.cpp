#include "mesh.h"
#include <algorithm>

template<typename T, glm::length_t N, glm::qualifier Q>
consteval glm::length_t count_of(const glm::vec<N, T, Q>& vec) {
    return N;
}

namespace ja {

    mesh::mesh() {
        // create vertex array
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        // create vertex buffer
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        // create element buffer
        glGenBuffers(1, &m_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

        // set attributes
        if constexpr (has_position<vertex>) {
            constexpr auto count = count_of(decltype(vertex::position){});
            glVertexAttribPointer(0, count, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(offsetof(vertex, position)));
            glEnableVertexAttribArray(0);
        }

        if constexpr (has_texcoord<vertex>) {
            constexpr auto count = count_of(decltype(vertex::position){});
            glVertexAttribPointer(1, count, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(offsetof(vertex, texcoord)));
            glEnableVertexAttribArray(1);
        }
    }

    mesh::~mesh() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
    }

    void mesh::clear() {
        m_vertices.clear();
        m_indices.clear();
    }

    void mesh::update_buffers() {
        glBindVertexArray(m_vao);

        // update the vertices
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(vertex), m_vertices.data(), GL_STATIC_DRAW);

        // update the indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), m_indices.data(), GL_STATIC_DRAW);
    }

    void mesh::draw() const {
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    }

    const std::vector<ja::vertex>& mesh::vertices() const {
        return m_vertices;
    }

    const std::vector<GLuint>& mesh::indices() const {
        return m_indices;
    }

}
