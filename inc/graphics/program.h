/**
 * @file program.h
 * @author Jochem Arends
 * @date 06-01-2024
 */

#ifndef PROGRAM_H
#define PROGRAM_H

#include <utility/handle.h>
#include <graphics/shader.h>
#include <expected>
#include <iostream>

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
        (glDetachShader(program.get(), shaders.get()), ...);
        return program;
    }

    /** 
     * Represents shader program related error codes.
     */
    enum class error_code {
        invalid_uniform_name,
        invalid_program
    };

    /**
     * Get location of uniform variable.
     *
     * @param program The program where the uniform variable is defined in.
     * @param name The name of the uniform variable.
     * @return The location of a uniform variable (if present).
     */
    std::expected<int, error_code> uniform_location(const handle& program, const char* name);

    /**
     * Get location of uniform variable.
     *
     * @param program The program where the uniform variable is defined in.
     * @param name The name of the uniform variable.
     * @return The location of a uniform variable (if present).
     */
    std::expected<int, error_code> uniform_location(const handle& program, const std::string& name);
}

#endif

