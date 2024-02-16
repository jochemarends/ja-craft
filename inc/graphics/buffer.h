/**
 * @file buffer.h
 * @author Jochem Arends
 * @date 07-01-2024
 */

#ifndef BUFFER_H
#define BUFFER_H

#include <utility/handle.h>
#include <glad/glad.h>

namespace ja::buffer {
    /**
     * A functor used to free buffer handles.
     */
    struct deleter {
        void operator()(GLuint buffer);
    };

    using handle = handle<GLuint, deleter>;

    /**
     * Creates a buffer.
     *
     * @return A buffer hanlde.
     */
    handle make();
}

#endif

