/**
 * @file texture_atlas.h
 * @author Jochem Arends
 * @date 25-04-2024
 */

#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include <graphics/texture.h>
#include <string>

namespace ja::texture_atlas {
    /**
     * Generates a 2D texture array given a texture atlas.
     *
     * @param file_name The path to the texture atlas.
     * @param row_count The amount of rows the texture atlas has.
     * @param column_count The amount of columns the texture atlas has.
     * @return The texture handle.
     */
    texture::handle from_file(const std::string& file_name, std::size_t row_count, std::size_t column_count);
}

#endif