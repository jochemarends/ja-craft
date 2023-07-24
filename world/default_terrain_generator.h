#ifndef JA__DEFAULT_TERRAIN_GENERATOR_H
#define JA__DEFAULT_TERRAIN_GENERATOR_H

#include "terrain_generator.h"
#include "../PerlinNoise.h"

namespace ja {

    class default_terrain_generator : terrain_generator {
    public:
        default_terrain_generator();
        void generate(ja::chunk& chunk) const override;
    private:
        siv::PerlinNoise m_noise;
    };

}

#endif
