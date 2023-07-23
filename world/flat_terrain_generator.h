#ifndef JA_FLAT_TERRAIN_GENERATOR_H
#define JA_FLAT_TERRAIN_GENERATOR_H

#include "chunk.h"

namespace ja {

    class flat_terrain_generator {
    public:
        void generate(ja::chunk& chunk) const;
    };

}

#endif
