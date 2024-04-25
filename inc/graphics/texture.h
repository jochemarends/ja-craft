/**
 * @file texture.h
 * @author Jochem Arends
 * @date 24-04-2024
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <utility/handle.h>

namespace ja::texture {
    /**
     * Functor used to free a shader.
     */
    struct deleter {
        void operator()(GLuint texture);
    };

    using handle = handle<GLuint, deleter>;

    /**
     * Create a texture.
     * @return The texture handle.
     */
    handle make();
}
#endif
