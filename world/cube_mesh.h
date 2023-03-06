#ifndef JA_CUBE_MESH_H
#define JA_CUBE_MESH_H

#include <glad/glad.h>

namespace ja {
    const GLfloat vertices[] {
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f,  0.5f
    };

    const GLfloat positions[] {
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f,  0.5f
    };

    const GLuint indices[] {
        0, 1, 2, 0, 2, 3, // back
        4, 5, 6, 4, 6, 7, // front
        0, 1, 5, 0, 5, 4, // left
        3, 2, 6, 3, 6, 7, // right
        1, 2, 6, 1, 6, 5, // up
        0, 3, 7, 0, 7, 4  // down
    };

    struct vertex {
        GLfloat pos[3];
        GLfloat tex[3];
    };

    struct mesh {
        vertex vertices[5];
        GLuint indices[6];
    };

    namespace face_mesh {
        constexpr std::size_t vertex_count = 4;
        constexpr std::size_t vertex_size  = 5;
        constexpr std::size_t size = vertex_count * vertex_size;
        using reference = GLfloat(&)[size];

        GLfloat front[]{
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f,  0.5f, 0.5f, 0.0f, 1.0f,
             0.5f,  0.5f, 0.5f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        };

        GLfloat back[]{
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
             0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        };

        GLfloat left[]{
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
        };

        GLfloat right[]{
             0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
             0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
        };

        GLfloat top[]{
            -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
        };

        GLfloat bottom[]{
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
             0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
             0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
        };
    }

    class chunk_mesh {
        using size_type = std::size_t;

        void add_face(glm::vec3 pos, face_mesh::reference face) {
            size_type idx_offset = m_vertex_data.size() / face_mesh::vertex_size
            for (int idx = 0; idx < face_mesh::size; idx += face_mesh::vertex_size) {
                // position data
                m_vertex_data.push_back(face[idx + 0] + x);
                m_vertex_data.push_back(face[idx + 1] + y);
                m_vertex_data.push_back(face[idx + 2] + z);

                // texture data
                m_indices.push_back(face[idx + 3]);
                m_indices.push_back(face[idx + 4]);
                m_indices.push_back(0);
            }
        }

        GLuint m_vbo, m_ebo, m_vao;
    }
}

#endif
