#include "program.h"
#include <string>

namespace ja {
    program::program(const shader& vert, const shader& frag) {
        // linking
        m_handle = glCreateProgram();
        glAttachShader(m_handle, vert.handle());
        glAttachShader(m_handle, frag.handle());
        glLinkProgram(m_handle);

        glDetachShader(m_handle, vert.handle());
        glDetachShader(m_handle, frag.handle());

        // checking for errors
        GLint status;
        glGetProgramiv(m_handle, GL_LINK_STATUS, &status);
        m_good = (status != GL_FALSE);
    }

    void program::use() const       { glUseProgram(m_handle); }
    GLuint program::uniform_location(const std::string& name) const { return glGetUniformLocation(m_handle, name.data()); }
    program::~program()             { glDeleteProgram(m_handle); }
    GLuint program::handle() const  { return m_handle; }
    bool program::good() const      { return m_good; }

    std::string program::info_log() const {
        GLint len;
        glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &len);
        std::string buffer;
        buffer.resize(len);
        glGetProgramInfoLog(m_handle, len, NULL, buffer.data());
        return buffer;
    }
}