#ifndef JA_FLAT_TERRAIN_GENERATOR_H
#define JA_FLAT_TERRAIN_GENERATOR_H

#include "terrain_generator.h"

namespace ja {

    class flat_terrain_generator : terrain_generator {
    public:
        void generate(ja::chunk& chunk) const override;
    };

}

#endif
