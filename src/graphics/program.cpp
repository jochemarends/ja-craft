#include <graphics/program.h>

namespace ja::program {
    void deleter::operator()(GLuint program) {
        if (program != 0) {
            glDeleteProgram(program);
        }
    }
}

