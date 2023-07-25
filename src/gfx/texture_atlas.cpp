#include "texture_atlas.h"
#include "../../stb_image.h"
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iostream>

texture_atlas::texture_atlas(const std::string& file_name, std::size_t rows, std::size_t columns)
    :m_rows{rows}, m_columns{columns} {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);

    GLubyte* data = stbi_load(file_name.c_str(), &width, &height, &channels, 0);

    if (data == nullptr) {
        throw std::runtime_error{stbi_failure_reason()};
    }

    glEnable(GL_TEXTURE_2D_ARRAY);

    constexpr int mipmap = 1;
    const int layers = rows * columns;
    glGenTextures(1, &m_handle);
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_handle);

    // wrapping parameters
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_LINEAR);

    // filtering parameters
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    auto tile_width = width / columns;
    auto tile_height = height / rows;
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, tile_width, tile_height, layers, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    auto column_stride = tile_width * channels;
    auto row_stride = column_stride * columns;

    std::vector<GLubyte> pixels(tile_width * tile_height * channels);

    for (int row{}; row < rows; ++row) {
        for (int column{}; column < columns; ++column) {
            GLubyte* ptr = data + row * tile_height * row_stride + column * column_stride;
            for (int i{}; i < tile_height; ++i) {
               std::copy(ptr + i * row_stride, ptr + i * row_stride + column_stride, pixels.begin() + i * column_stride);
            }
//            for (int i{}; i < tile_height; ++i) {
//                std::copy(ptr + i * row_stride, ptr + i * row_stride + column_stride, pixels.begin() + i * column_stride);
//            }
//            for (int i{}; i < tile_height; ++i) {
//                std::copy(ptr + i * row_stride, ptr + i * row_stride + column_stride, pixels.begin() + (tile_height - 1 - i) * column_stride);
//            }
            int idx = (rows - 1 - row) * columns + column;
            std::cout << idx << '\n';
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, idx, tile_width, tile_height, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
        }
    }



    //glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, tile_width, tile_height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}