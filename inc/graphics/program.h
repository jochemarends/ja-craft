/**
 * @file program.h
 * @author Jochem Arends
 * @date 06-01-2024
 */

#ifndef PROGRAM_H
#define PROGRAM_H

#include <utility/handle.h>
#include <graphics/shader.h>

namespace ja::program {
    /**
     * A functor used to free program handles.
     */
    struct deleter {
        void operator()(GLuint program);
    };
    
    using handle = handle<GLuint, deleter>;

    /**
     * Create program.
     *
     * Creates a program given an arbitrary amount of shaders.
     *
     * @tparam Ts A parameter pack where each type is of shader::handle.
     * @param shaders The shaders.
     * @return A program handle.
     */
    template<typename... Ts>
    requires (std::same_as<shader::handle, Ts> && ...)
    handle make(const Ts&... shaders) {
        handle program{glCreateProgram()};
        (glAttachShader(program.get(), shaders.get()), ...);
        glLinkProgram(program.get());
        return program;
    }
}

#endif

