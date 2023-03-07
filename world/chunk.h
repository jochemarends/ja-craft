#ifndef JA_CHUNK_H
#define JA_CHUNK_H

#include <glad/glad.h>
#include <vector>

namespace ja {
    class chunk {
        static constexpr std::size_t width  = 16;
        static constexpr std::size_t height = 16;
        static constexpr std::size_t depth  = 16;
    private:
        std::vector<GLfloat> vertices;
    };
}

#endif
