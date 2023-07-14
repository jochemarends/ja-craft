#ifndef JA_CRAFT_MESH_H
#define JA_CRAFT_MESH_H

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <vector>
#include <span>
#include <algorithm>
#include <ranges>
#include <concepts>
#include <memory>

namespace ja {
    enum class face {
        front, back, left, right, top, bottom
    };

    struct vertex {
        glm::vec3 position;
        glm::vec3 texcoord;
    };


    template<typename T>
    concept has_position = requires {
        &T::position;
    };

    template<typename T>
    concept has_texcoord = requires {
        &T::texcoord;
    };

    template<typename T, glm::length_t N, glm::qualifier Q>
    consteval glm::length_t count_of(const glm::vec<N, T, Q>& vec) {
        return N;
    }

    class mesh {
    public:
        mesh();
        ~mesh();
        mesh(const mesh&) = delete;
        mesh& operator=(const mesh&) = delete;

        template<std::ranges::input_range R, typename Proj = std::identity>
        requires std::same_as<std::ranges::range_value_t<R>, vertex>
        void add_vertices(const R& vertices, Proj proj = {});

        template<std::ranges::input_range R>
        requires std::same_as<std::ranges::range_value_t<R>, GLuint>
        void add_indices(const R& indices, GLuint offset = 0);

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

    template<std::ranges::input_range R, typename Proj>
    requires std::same_as<std::ranges::range_value_t<R>, vertex>
    void mesh::add_vertices(const R& vertices, Proj proj) {
        std::ranges::transform(vertices, std::back_inserter(m_vertices), proj);
    }

    template<std::ranges::input_range R>
    requires std::same_as<std::ranges::range_value_t<R>, GLuint>
    void mesh::add_indices(const R& indices, GLuint offset) {
        for (auto idx : indices) m_indices.push_back(idx + offset);
    }
}

#endif
