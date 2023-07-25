#ifndef JA_CRAFT_CHUNK_H
#define JA_CRAFT_CHUNK_H

#include "glad/glad.h"
#include <map>
#include <glm/gtc/type_ptr.hpp>
#include "../gfx/mesh.h"
#include <vector>
#include <optional>
#include <unordered_map>
#include "../physics/aabb.h"
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

    inline static std::unordered_map<face, const vertex(&)[4]> vertices_of{
        {face::front,  front },
        {face::back,   back  },
        {face::left,   left  },
        {face::right,  right },
        {face::top,    top   },
        {face::bottom, bottom}
    };

    inline static std::unordered_map<face, glm::vec3> normal_of{
            {face::front,  { 0.0f,  0.0f,  1.0f}},
            {face::back,   { 0.0f,  0.0f, -1.0f}},
            {face::left,   {-1.0f,  0.0f,  0.0f}},
            {face::right,  { 1.0f,  0.0f,  0.0f}},
            {face::top,    { 0.0f,  1.0f,  0.0f}},
            {face::bottom, { 0.0f, -1.0f,  0.0f}}
    };

    inline static face faces[]{
        face::front,
        face::back,
        face::left,
        face::right,
        face::top,
        face::bottom
    };

    enum block : std::uint8_t {
        grass, dirt, clay, brick, glass, flag,
        empty
    };

    bool is_transparant(block b);

    // front, back, left, right, top, bottom
    inline static std::unordered_map<block, std::array<int, 6>> texture_indices{
        {block::grass, {0, 0, 0, 0, 0, 0}},
        {block::dirt,  {1, 1, 1, 1, 1, 1}},
        {block::brick, {6, 6, 6, 6, 6, 6}},
        {block::clay,  {5, 5, 5, 5, 5, 5}},
        {block::glass, {10, 10, 10, 10, 10, 10}},
        {block::flag,  {11, 11, 11, 11, 15, 16}}
    };

    class terrain;

    class chunk {
    public:
        static constexpr int width  = 16;
        static constexpr int height = 16;
        static constexpr int depth  = 16;

        chunk(ja::terrain& terrain);
        void generate();

        block(&data())[width][height][depth];
        const block(&data() const)[width][height][depth];

        glm::vec3 pos() const;
        glm::vec3 pos(std::size_t i, std::size_t j, std::size_t k) const;

        ja::aabb aabb() const;
        ja::aabb aabb(std::size_t i, std::size_t j, std::size_t k) const;

        void build_mesh();
        const mesh& mesh() const;

        glm::ivec3 id() const;
        void set_id(int i, int j, int k);
    private:
        terrain& m_terrain;
        block m_data[width][height][depth];
        glm::ivec3 m_id;
        ja::mesh m_mesh;
    };
}

#endif
