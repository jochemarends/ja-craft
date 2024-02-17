/**
 * @file mesh.h
 * @author Jochem Arends
 * @date 17-02-2024
 */

#ifndef MESH_H
#define MESH_H

#include <graphics/buffer.h>
#include <graphics/vertex.h>
#include <graphics/vertex_array.h>
#include <ranges>

namespace ja {
    /**
     * A graphics mesh.
     *
     * A collection of vertices (and indices).
     *
     * @note Mesh can only consist of vertices of ja::vertex type at the moment.
     */
    struct mesh {
        /**
         * Create a mesh from vertices.
         *
         * @tparam R Type that is a range and can hold vertices.
         * @param vertices Sequence of vertices.
         * @return A mesh instance.
         *
         * @note Binds the underlying buffer to GL_ARRAY_BUFFER.
         */
        template<std::ranges::contiguous_range R>
        requires std::same_as<std::ranges::range_value_t<R>, vertex>
        static mesh from(R&& vertices);

        /**
         * Create a mesh from vertices and indices.
         *
         * @tparam R1 Type that is a range and can hold vertices.
         * @tparam R2 Type that is a range and can hold indices. 
         * @param vertices Sequence of vertices.
         * @param indices Sequence of indices.
         * @return A mesh instance.
         *
         * @note Binds the underlying buffers to GL_ARRAY_BUFFER and GL_ELEMENT_ARRAY_BUFFER.
         */
        template<std::ranges::contiguous_range R1, std::ranges::contiguous_range R2>
        requires std::same_as<std::ranges::range_value_t<R1>, vertex> &&
                 std::same_as<std::ranges::range_value_t<R2>, GLuint>
        static mesh from(R1&& vertices, R2&& indices);

        void reset();

        void push_back();

        void bind() const;
    private:
        mesh() = default;

        /**
         * Loads a sequence of vertices in the buffer.
         * 
         * @tparam R Type that is a range and can hold vertices. 
         * @param indices Sequence of vertices.
         *
         * @note Overrides earlier loaded data.
         */
        template<std::ranges::contiguous_range R>
        requires std::same_as<std::ranges::range_value_t<R>, vertex>
        void load_vertices(R&& vertices);

        /**
         * Loads a sequence of indices in the buffer.
         * 
         * @tparam R Type that is a range and can hold indices. 
         * @param indices Sequence of indices.
         *
         * @note Overrides earlier loaded data.
         */
        template<std::ranges::contiguous_range R>
        requires std::same_as<std::ranges::range_value_t<R>, GLuint>
        void load_indices(R&& indices);

        vertex_array::handle m_vao = vertex_array::make();
        buffer::handle m_abo = buffer::make();
        buffer::handle m_ebo = buffer::make();
    };
}

#endif

