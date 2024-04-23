/**
 * @file vertex_array.h
 * @author Jochem Arends
 * @date 07-01-2024
 */

#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <utility/handle.h>
#include <glad/glad.h>

namespace ja::vertex_array {
    /**
     * A functor used to free vertex array handles.
     */
    struct deleter {
        void operator()(GLuint vbo);
    };

    using handle = handle<GLuint, deleter>;

    /**
     * Creates a vertex array.
     *
     * @return A vertex array handle.
     */
    handle make();
}

#endif

