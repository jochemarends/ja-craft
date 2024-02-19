#include <graphics/program.h>

namespace ja::program {
    void deleter::operator()(GLuint program) {
        if (program != 0) {
            glDeleteProgram(program);
        }
    }

    std::expected<int, error_code> uniform_location(const handle& program, const char* name) {
        // don't care about previous occurred errors if we still haven't
        // dealt with them by now
        while (glGetError() != GL_NO_ERROR);

        auto loc = glGetUniformLocation(program.get(), name);

        if (loc == -1) {
            return std::unexpected(error_code::invalid_uniform_name);
        }
        else if (auto error = glGetError(); error != GL_NO_ERROR) {
            return std::unexpected(error_code::invalid_program);
        }

        return loc;
    }

    std::expected<int, error_code> uniform_location(const handle& program, std::string& name) {
        return uniform_location(program, name.c_str());
    }
}

