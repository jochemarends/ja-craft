/**
 * @file mesh.h
 * @author Jochem Arends
 * @date 17-02-2024
 */

#include <glm/glm.hpp>

namespace ja {
    /**
     * A graphics vertex.
     *
     * The building block of a mesh. point in 3D space and also hold a texture coordinate.
     */
    struct vertex {
        glm::vec3 m_position{}; /**< Point in 3D space. */
        glm::vec3 m_texcoord{}; /**< Texture coordinate. */
    };
}
