#include "flat_terrain_generator.h"

namespace ja {

    void flat_terrain_generator::generate(ja::chunk &chunk) const {
        for (int i{}; i < chunk::width; ++i) {
            for (int j{}; j < chunk::depth; ++j) {
                chunk.data()[i][0][j] = block::grass;
            }
        }
    }

}