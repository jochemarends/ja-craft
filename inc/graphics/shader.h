/**
 * @file handle.h
 * @author Jochem Arends
 * @date 06-01-2024
 */

#ifndef SHADER_H
#define SHADER_H

#include <utility/handle.h>
#include <glad/glad.h>
#include <string>

namespace ja::shader {
    /**
     * A functor used to free shader handles.
     */
    struct deleter {
        void operator()(GLuint shader);
    };

    using handle = handle<GLuint, deleter>;

    /**
     * Create shader from file.
     *
     * @param type A shader type.
     * @param file_name A name to a file that contains the source code.
     * @return A shader handle.
     */
    handle from_file(GLenum type, const std::string& file_name);

    /**
     * Create shader from text.
     *
     * @param type A shader type.
     * @param text Contains the source code of the shader program.
     * @return A shader handle.
     */
    handle from_text(GLenum type, const std::string_view text);

    /**
     * Checks whether a shader is in valid state.
     *
     * @param shader The shader to check.
     * @return A boolean indicating whether the shader is in a valid state.
     */
    bool good(const handle& shader);

    /**
     * Retrieve a potential error message.
     *
     * Retreives a potential error message belonging to a shader or an empty string
     * if the shader is in a valid state.
     *
     * @param shader The shader to check.
     * @return The message.
     */
    std::string what(const handle& shader);

    /**
     * Retrieve info log of shader.
     *
     * @param shader A shader.
     * @return The info log.
     * @note The passed shader must be in a valid state.
     */
    std::string info_log(const handle& shader);
}

#endif

