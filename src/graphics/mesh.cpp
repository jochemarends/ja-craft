/**
 * @file mesh.cpp
 * @author Jochem Arends
 * @date 17-02-2024
 */

#include <graphics/mesh.h>
#include <memory>

namespace ja {
    template<std::ranges::contiguous_range R>
    requires std::same_as<std::ranges::range_value_t<R>, vertex>
    static mesh from(R&& vertices) {
        return from(vertices, std::ranges::empty_view<GLuint>{});
    }

    template<std::ranges::contiguous_range R1, std::ranges::contiguous_range R2>
    requires std::same_as<std::ranges::range_value_t<R1>, vertex> &&
             std::same_as<std::ranges::range_value_t<R2>, GLuint>
    static mesh from(R1&& vertices, R2&& indices) {
        mesh m{};
        m.load_vertices(vertices);
        m.load_indices(indices);
        return m;
    }

    template<std::ranges::contiguous_range R>
    requires std::same_as<std::ranges::range_value_t<R>, vertex>
    void load_vertices(R&& vertices) {
        auto ptr = std::to_address(std::ranges::begin(vertices));
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo.get());

        auto size = std::ranges::size(vertices);
        auto bytes = size * sizeof(std::ranges::range_value_t<R>)
        glBufferData(GL_ARRAY_BUFFER, bytes, ptr, GL_STATIC_DRAW);
    }

    template<std::ranges::contiguous_range R>
    requires std::same_as<std::ranges::range_value_t<R>, GLuint>
    void mesh::load_indices(R&& indices) {
        auto ptr = std::to_address(std::ranges::begin(indices));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo.get());

        auto size = std::ranges::size(indices);
        auto bytes = size * sizeof(std::ranges::range_value_t<R>)
        glBufferData(GL_ARRAY_BUFFER, bytes, ptr, GL_STATIC_DRAW);
    }
}

