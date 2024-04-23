#include <graphics/shader.h>
#include <fstream>
#include <iterator>

namespace ja::shader {
    void deleter::operator()(GLuint shader) {
        if (shader != 0) {
            glDeleteShader(shader);
        }
    }

    handle from_file(GLenum type, const std::string& file_name) {
        std::ifstream ifs{file_name};
        if (!ifs) return handle{0};

        ifs >> std::noskipws;
        std::string text{std::istream_iterator<char>{ifs}, std::istream_iterator<char>{}};
        
        return from_text(type, text);
    }

    handle from_text(GLenum type, std::string_view text) {
        handle shader{glCreateShader(type)};

        const char* data = text.data();
        auto size = static_cast<int>(text.size());

        glShaderSource(shader.get(), 1, &data, &size);
        glCompileShader(shader.get());

        return shader;
    }

    bool good(const handle& shader) {
        if (shader.get() == 0) return false;
        GLint status{};
        glGetShaderiv(shader.get(), GL_COMPILE_STATUS, &status);
        return status != GL_FALSE;
    }

    std::string what(const handle& shader) {
        if (shader.get() == 0) {
            return "ERROR: failed to create shader";
        }
        return info_log(shader);
    }

    std::string info_log(const handle& shader) {
        GLint len{};
        glGetShaderiv(shader.get(), GL_INFO_LOG_LENGTH, &len);

        std::string buffer{};
        buffer.resize(len);

        glGetShaderInfoLog(shader.get(), len, nullptr, buffer.data());
        return buffer;
    }
}

