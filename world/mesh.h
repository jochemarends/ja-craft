#ifndef JA_CRAFT_MESH_H
#define JA_CRAFT_MESH_H

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <vector>
#include <span>
#include <algorithm>
#include <ranges>
#include <concepts>

namespace ja {
    enum class face {
        front, back, left, right, top, bottom
    };

    struct vertex {
        glm::vec3 position;
        glm::vec2 texcoord;
    };

    class mesh {
    public:
        mesh();
        ~mesh();
        mesh(const mesh&) = delete;
        mesh& operator=(const mesh&) = delete;

        template<typename T, std::size_t N, typename Proj = std::identity>
        requires std::same_as<typename std::remove_const<T>::type, vertex>
        void add_vertices(std::span<T, N> vertices, Proj proj = {});

        template<typename T, std::size_t N>
        requires std::same_as<typename std::remove_const<T>::type, GLuint>
        void add_indices(std::span<T, N> indices, GLuint offset = 0);

        void clear();
        void update_buffers();
        void draw() const;

        const std::vector<vertex>& vertices() const;
        const std::vector<GLuint>& indices() const;
    private:
        std::vector<vertex> m_vertices;
        std::vector<GLuint> m_indices;
        GLuint m_vbo, m_ebo, m_vao;
    };

    template<typename T, std::size_t N, typename Proj>
    requires std::same_as<typename std::remove_const<T>::type, vertex>
    void ja::mesh::add_vertices(std::span<T, N> vertices, Proj proj) {
        std::ranges::transform(vertices, std::back_inserter(m_vertices), proj);
    }

    template<typename T, std::size_t N>
    requires std::same_as<typename std::remove_const<T>::type, GLuint>
    void ja::mesh::add_indices(std::span<T, N> indices, GLuint offset) {
        for (auto idx : indices) m_indices.push_back(idx + offset);
    }
}

#endif
