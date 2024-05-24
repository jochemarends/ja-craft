#include <world/cube.h>

namespace ja::cube {
    namespace {
        template<face>
        const std::array<vertex, 4> vertices_of;

        template<>
        const std::array<vertex, 4> vertices_of<face::front>{
            vertex{{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}},
            vertex{{-0.5f, 0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},
            vertex{{0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}},
            vertex{{0.5f,  -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}},
        };

        template<>
        const std::array<vertex, 4> vertices_of<face::back>{
            vertex{{0.5f,  -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            vertex{{0.5f,  0.5f,  -0.5f}, {1.0f, 1.0f, 0.0f}},
            vertex{{-0.5f, 0.5f,  -0.5f}, {0.0f, 1.0f, 0.0f}},
            vertex{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}},
        };

        template<>
        const std::array<vertex, 4> vertices_of<face::left>{
            vertex{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}},
            vertex{{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            vertex{{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}},
            vertex{{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
        };

        template<>
        const std::array<vertex, 4> vertices_of<face::right>{
            vertex{{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
            vertex{{0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}},
            vertex{{0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            vertex{{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}},
        };

        template<>
        const std::array<vertex, 4> vertices_of<face::top>{
            vertex{{-0.5f, 0.5f,  0.5f}, {0.0f, 0.0f, 0.0f}},
            vertex{{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            vertex{{0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}},
            vertex{{0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
        };

        template<>
        const std::array<vertex, 4> vertices_of<face::bottom>{
            vertex{{0.5f,  -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
            vertex{{0.5f,  -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}},
            vertex{{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            vertex{{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 0.0f}},
        };
    }

    std::span<const vertex, 4> face_vertices(face f) {
        switch (f) {
            case face::front:
                return vertices_of<face::front>;
            case face::back:
                return vertices_of<face::back>;
            case face::left:
                return vertices_of<face::left>;
            case face::right:
                return vertices_of<face::right>;
            case face::top:
                return vertices_of<face::top>;
            case face::bottom:
            default:
                return vertices_of<face::bottom>;
        }
    }
}

