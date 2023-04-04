#ifndef JA_CRAFT_CHUNK_H
#define JA_CRAFT_CHUNK_H

#include <glad/glad.h>
#include <vector>
#include <map>
#include <glm/gtc/type_ptr.hpp>
#include "mesh.h"
#include "aabb.h"

namespace ja {
    inline static const vertex front[]{
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f}},
            {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},
    };

    inline static const vertex back[]{
            {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
    };

    inline static const vertex left[]{
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},
            {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}},
            {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},
    };

    inline static const vertex right[]{
            {{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},
            {{0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}},
            {{0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},
            {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
    };

    inline static const vertex top[]{
            {{-0.5f, 0.5f,  0.5f}, {0.0f, 0.0f}},
            {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}},
            {{ 0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},
            {{ 0.5f, 0.5f,  0.5f}, {1.0f, 0.0f}},
    };

    inline static const vertex bottom[]{
            {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},
            {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
    };

    inline static const GLuint indices[]{
        0, 1, 2, 0, 2, 3
    };

    class chunk {
        class iterator;
    public:
        static constexpr std::size_t width  = 16;
        static constexpr std::size_t height = 16;
        static constexpr std::size_t depth  = 16;

        void generate();
        const mesh& mesh() const { return m_mesh; }
        ja::aabb aabb(std::size_t i, std::size_t j, std::size_t k) const;
        bool m_data[width][height][depth]{1};
    private:
        ja::mesh m_mesh;
    };

    class chunk::iterator {
    public:
        iterator(chunk& chunk, glm::uvec3 idx);
        glm::vec3 position() const;
        glm::uvec3 index() const;
        ja::aabb aabb() const;
    private:
        chunk& m_chunk;
        glm::uvec3 m_idx;
    };
}

#endif
