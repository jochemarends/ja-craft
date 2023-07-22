#include "generator.h"

namespace ja {

    generator::generator()
        :m_seed{}, m_noise{m_seed} {}

    void generator::generate(chunk& chunk) const {
        for (std::size_t i{}; i < chunk::width; ++i) {
            for (std::size_t j{}; j < chunk::depth; ++j) {

            }
        }
        for (auto [i, j, k] : indices_of(chunk.data())) {
            auto v = chunk.pos(i, j, k) * 0.01f;
            auto height = m_noise.noise2D_01(v.x, v.z) * chunk::height;

            if (p >= j) {
                chunk.data()[i][j][k] = (std::abs(p - j) < 0.6) ? block::dirt : block::dirt;
        }
        }
    }

}
