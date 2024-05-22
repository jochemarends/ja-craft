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
    }

    std::span<const vertex, 4> face_vertices(face f) {
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
            default:
                return vertices<face::bottom>;
        }
    }
}

