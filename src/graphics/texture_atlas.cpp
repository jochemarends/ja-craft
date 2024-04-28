/**
 * @file texture_atlas.cpp
 * @author Jochem Arends
 * @date 25-04-2024
 */

#include <algorithm>
#include <ranges>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <graphics/texture_atlas.h>

namespace ja::texture_atlas {
    texture::handle from_file(const std::string& file_name, std::size_t row_count, std::size_t column_count) {
        // load the image's pixel data in memory
        int width{}, height{}, channels{};
        GLubyte* data = stbi_load(file_name.c_str(), &width, &height, &channels, 0);

        // check for errors
        if (data == nullptr) {
            using namespace std::literals::string_literals;
            throw std::runtime_error{"ERROR: "s.append(stbi_failure_reason())};
        }

        texture::handle texture = texture::make();
        glBindTexture(GL_TEXTURE_2D_ARRAY, texture.get());

        // wrapping parameters
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_LINEAR);

        // filtering parameters
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        const auto tile_count = static_cast<int>(row_count * column_count);
        const auto tile_width = static_cast<int>(width / column_count);
        const auto tile_height = static_cast<int>(height / row_count);
        const auto column_stride = tile_width * channels;

        // for getting a format based on the amount of channels
        const std::unordered_map<int, GLint> format{{3, GL_RGB}, {4, GL_RGBA}};

        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, format.at(channels), tile_width, tile_height, tile_count, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        // use a proper range so it works with range adaptors
        std::size_t size = width * height * channels;
        std::span<GLubyte> image{data, size};

        // before generating a texture for a tile, the pixel data of that tile has to be copied to a buffer since
        // OpenGL requires pixel data to be stored contiguously
        std::vector<GLubyte> buffer{};
        const std::size_t tile_size = tile_width * tile_height * channels;
        buffer.reserve(tile_size);

        std::ranges::iota_view rows{0uz, row_count}, columns{0uz, column_count};
        for (auto [row, column]: std::views::cartesian_product(rows, columns)) {
            const auto layer = static_cast<int>(row * column_count + column);

            // extract tile from image
            auto tile = image | std::views::chunk(column_stride)
                              | std::views::drop(row * column_count + column)
                              | std::views::stride(column_count)
                              | std::views::take(tile_height)
                              | std::views::join;

            buffer.clear();
            std::ranges::copy(tile, std::back_inserter(buffer));
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, layer, tile_width, tile_height, 1, format.at(channels), GL_UNSIGNED_BYTE, buffer.data());
        }

        return texture;
    }
}
