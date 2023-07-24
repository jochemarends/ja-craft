#include "default_terrain_generator.h"

namespace ja {

    default_terrain_generator::default_terrain_generator()
        :m_noise{0} {}

    void default_terrain_generator::generate(ja::chunk &chunk) const {
        for (int i{}; i < chunk::width; ++i) {
            for (int j{}; j < chunk::depth; ++j) {
                int x = chunk.pos(i, 0, j).x;
                int z = chunk.pos(i, 0, j).z;

                int height = m_noise.noise2D_01(x * 0.1, z * 0.1) * chunk::height;
                for (int y{}; y < height; ++y) {
                    chunk.data()[i][y][j] = block::grass;
                }
            }
        }
    }

}