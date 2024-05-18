#include <world/cube.h>

namespace ja::cube {
    namespace {
        template<face>
        const std::array<vertex, 4> vertices;

        template<>
        const std::array<vertex, 4> vertices<face::front>{
            vertex{{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}},
            vertex{{-0.5f, 0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},
            vertex{{0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}},
            vertex{{0.5f,  -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}},
        };

        template<>
        const std::array<vertex, 4> vertices<face::back>{
            vertex{{0.5f,  -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            vertex{{0.5f,  0.5f,  -0.5f}, {1.0f, 1.0f, 0.0f}},
            vertex{{-0.5f, 0.5f,  -0.5f}, {0.0f, 1.0f, 0.0f}},
            vertex{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}},
        };

        template<>
        const std::array<vertex, 4> vertices<face::left>{
            vertex{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}},
            vertex{{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            vertex{{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}},
            vertex{{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
        };

        template<>
        const std::array<vertex, 4> vertices<face::right>{
            vertex{{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
            vertex{{0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}},
            vertex{{0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            vertex{{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}},
        };

        template<>
        const std::array<vertex, 4> vertices<face::top>{
            vertex{{-0.5f, 0.5f,  0.5f}, {0.0f, 0.0f, 0.0f}},
            vertex{{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            vertex{{0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}},
            vertex{{0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
        };

        template<>
        const std::array<vertex, 4> vertices<face::bottom>{
            vertex{{0.5f,  -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
            vertex{{0.5f,  -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}},
            vertex{{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            vertex{{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 0.0f}},
        };

        auto face_vertices(face f) {
            switch (f) {
                case face::front:
                    return vertices<face::front>;
                case face::back:
                    return vertices<face::back>;
                case face::left:
                    return vertices<face::left>;
                case face::right:
                    return vertices<face::right>;
                case face::top:
                    return vertices<face::top>;
                case face::bottom:
                    return vertices<face::bottom>;
            }
        }
    }

    auto face_vertices(face f, block b) {
        return std::views::transform(face_vertices(f), [b](vertex vert) {
            vert.m_texcoord.z = static_cast<float>(block_traits::texture_index(b));
            return vert;
        });
    }
}

