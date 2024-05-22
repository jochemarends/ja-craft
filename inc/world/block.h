#ifndef BLOCK_H
#define BLOCK_H

#include <cstdint>

namespace ja {
    /**
     * Used for representing different block types
     */
    enum class block : std::uint8_t {
        empty, 
        grass,
    };

    namespace block_traits {
        /**
         * For obtaining the texture index given a block type.
         *
         * @param b The block to obtain the texture index for.
         * @return The texture index.
         */
        inline std::size_t texture_index([[maybe_unused]] block b) {
            return 0uz;
        }

        /**
         * Determines whether a block is transparent.
         *
         * @param b A block type to check for transparency.
         * @return A boolean value indicating whether the passed block type is transparent.
         */
        bool is_transparent(block b);
    }
}

#endif

