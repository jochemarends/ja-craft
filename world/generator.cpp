#include "generator.h"

namespace ja {

    generator::generator()
        :m_seed{}, m_noise{m_seed} {}

    void generator::generate(chunk& chunk) const {
        for (std::size_t i{}; i < chunk::width; ++i) {
            for (std::size_t j{}; j < chunk::depth; ++j) {

            }
        }
    }

}
