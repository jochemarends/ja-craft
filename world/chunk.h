#ifndef JA_CRAFT_CHUNK_H
#define JA_CRAFT_CHUNK_H

#include <glad/glad.h>
#include <map>
#include <glm/gtc/type_ptr.hpp>
#include "mesh.h"
#include "aabb.h"
#include <vector>
#include <optional>
#include <unordered_map>
#include "../util/indices_view.h"

namespace ja {
    inline static const vertex front[]{
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
    };

    inline static const vertex back[]{
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}},
    };

    inline static const vertex left[]{
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
    };

    inline static const vertex right[]{
        {{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}},
        {{0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}},
    };

    inline static const vertex top[]{
        {{-0.5f, 0.5f,  0.5f}, {0.0f, 0.0f, 0.0f}},
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{ 0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}},
        {{ 0.5f, 0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
    };

    inline static const vertex bottom[]{
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 0.0f}},
    };

    inline static const GLuint indices[]{
        0, 1, 2, 0, 2, 3
    };

    enum block : std::uint8_t {
        grass, dirt, brick, clay, empty
    };

    // front, back, left, right, top, bottom
    inline static std::unordered_map<block, std::array<int, 6>> texture_indices{
            {block::grass, {0, 1, 2, 3, 0, 1}},
            {block::dirt,  {1, 1, 1, 1, 1, 1}},
            {block::brick, {2, 2, 2, 2, 2, 2}},
            {block::clay,  {3, 3, 3, 3, 3, 3}},
    };

    class chunk {
    public:
        class iterator;
        static constexpr std::size_t width  = 16;
        static constexpr std::size_t height = 16;
        static constexpr std::size_t depth  = 16;
        chunk();
        void generate();
        const glm::vec3& position() const { return m_position; }
        const mesh& mesh() const { return m_mesh; }
        ja::aabb aabb(std::size_t i, std::size_t j, std::size_t k) const;
        glm::vec3 pos(std::size_t i, std::size_t j, std::size_t k) const;
        std::optional<std::pair<tuple_of_n<std::size_t, 3>::type, face>> test(ja::ray indices) const;
        using data_type = block[width][height][depth];
        data_type& data();
        data_type m_data{block::grass};
        glm::vec3 m_position;
        ja::mesh m_mesh;
    private:
    };

    class chunk::iterator {
    public:
        iterator(const chunk& chunk, glm::uvec3 idx);
        glm::vec3 position() const;
        glm::uvec3 index() const;
        ja::aabb aabb() const;
    private:
        const chunk& m_chunk;
        glm::uvec3 m_idx;
    };
}

#endif
