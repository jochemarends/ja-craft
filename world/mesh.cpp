#include "mesh.h"
#include <algorithm>

ja::mesh::mesh() {
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(offsetof(vertex, position)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(offsetof(vertex, texcoord)));
    glEnableVertexAttribArray(1);


//    update_buffers();
}

ja::mesh::~mesh() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

void ja::mesh::clear() {
    m_vertices.clear();
    m_indices.clear();
}

void ja::mesh::update_buffers() {
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(vertex), m_vertices.data(), GL_DYNAMIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), m_indices.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(vertex), m_vertices.data());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indices.size() * sizeof(GLuint), m_indices.data());
}

void ja::mesh::draw() const {
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
}

const std::vector<ja::vertex>& ja::mesh::vertices() const {
    return m_vertices;
}

const std::vector<GLuint>& ja::mesh::indices() const {
    return m_indices;
}
