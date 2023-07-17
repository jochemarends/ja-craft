#include <iostream>
#include "terrain.h"
#include "../gfx/program.h"

namespace ja {

    terrain::terrain() {
        for (auto [i, j] : indices_of(m_chunks)) {
            m_chunks[i][j].m_position = {i * 16, 0, j * 16};

            chunk& chunk = m_chunks[i][j];
            for (auto [i, j, k] : indices_of(chunk.data())) {
                if (j == 0) {
//                    chunk.data()[i][j][k] = block::dirt;
                } else {
//                    chunk.data()[i][j][k] = block::empty;
                }
            }

            m_chunks[i][j].generate();
        }

    }

    chunk& terrain::chunk_at(const glm::vec3& pos) {
//        position
        auto [i, j] = pos_to_idx(pos);
//            std::cout << '[' << i << ',' << j << "]\n";
        return m_chunks[i][j];
    }

    void terrain::draw(const ja::program& program) const {
        for (auto [i, j] : indices_of(m_chunks)) {
            glm::mat4 model{1};
            model = glm::translate(model, m_chunks[i][j].m_position);
            glUniformMatrix4fv(program.uniform_location("model"), 1, GL_FALSE, glm::value_ptr(model));
            m_chunks[i][j].m_mesh.draw();
        }
    }

    tuple_of_n<std::size_t, 2> terrain::pos_to_idx(glm::vec3 pos) const {
        return {
                (pos.x - m_position.x) / chunk::width,
                (pos.z - m_position.z) / chunk::depth
        };
    }

    tuple_of_n<int, 2> terrain::new_pos_to_idx(glm::vec3 pos) {
            return {
                    (pos.x - m_position.x) / chunk::width,
                    (pos.z - m_position.z) / chunk::depth
            };
    }

    glm::vec3 terrain::idx_to_pos(std::size_t i, std::size_t j) const {
        return {i * chunk::width, 0, j * chunk::depth};
    }

    void terrain::center_to(const glm::vec3& pos) {
        auto set_pos = [](auto& chunk, int i, int j) {
            chunk.m_position.x = i * chunk::width;
            chunk.m_position.z = j * chunk::depth;
        };

        auto [x, y] = new_pos_to_idx(pos);
        for (auto [i, j] : indices_of(m_chunks)) {
            set_pos(m_chunks[i][j], x - 1, y - 1);
        }
    }

}