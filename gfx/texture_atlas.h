#ifndef JA_TEXTURE_ATLAS_H
#define JA_TEXTURE_ATLAS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string_view>
#include "../util/non_copyable.h"

class texture_atlas : non_copyable {
public:
    texture_atlas(const std::string& file_name, std::size_t rows, std::size_t columns);
    GLuint m_handle;
    std::size_t m_rows{}, m_columns{};
};


#endif
