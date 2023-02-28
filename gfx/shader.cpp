#include "shader.h"
#include <fstream>
#include <string>
#include <iterator>

namespace ja {
    shader::shader(shader::type type, std::string_view filename) {
        std::ifstream ifs{filename.data()};
        if (!ifs) return;

        // read the content of the file
        ifs >> std::noskipws;
        std::string source{std::istream_iterator<char>(ifs), std::istream_iterator<char>{}};

        // compiling
        m_handle = glCreateShader(static_cast<GLenum>(type));
        const char* c_str = source.c_str();
        glShaderSource(m_handle, 1, &c_str, NULL);
        glCompileShader(m_handle);

        // checking for errors
        GLint status;
        glGetShaderiv(m_handle, GL_COMPILE_STATUS, &status);
        m_good = (status != GL_FALSE);
    }

    shader::~shader() { glDeleteShader(m_handle); }
    bool shader::good() const { return m_good; }
    GLuint shader::handle() const { return m_handle; }

    std::string shader::info_log() const {
        GLint len;
        glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &len);
        std::string buffer;
        buffer.resize(len);
        glGetShaderInfoLog(m_handle, len, NULL, buffer.data());
        return buffer;
    }
}