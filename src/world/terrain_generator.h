#ifndef JA_TERRAIN_GENERATOR_H
#define JA_TERRAIN_GENERATOR_H

#include "chunk.h"

namespace ja {

    class terrain_generator {
        virtual void generate(ja::chunk& chunk) const = 0;
    };

}

#endif
