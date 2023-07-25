#ifndef JA_GENERATOR_H
#define JA_GENERATOR_H

#include "../../PerlinNoise.h"
#include "chunk.h"

namespace ja {

    class generator {
    public:
        generator();
        void generate(chunk& chunk) const;
    private:
        siv::PerlinNoise::seed_type m_seed;
        siv::PerlinNoise m_noise;
    };

}

#endif
