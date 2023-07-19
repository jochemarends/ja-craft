#include <iostream>
#include "terrain.h"
#include "../gfx/program.h"
#include "../PerlinNoise.h"

namespace ja {

    chunk(&terrain::chunks())[terrain::width][terrain::depth] {
        return m_chunks;
    }

    const chunk(&terrain::chunks() const)[terrain::width][terrain::depth] {
        return m_chunks;
    }

    void foo(ja::chunk& chunk, const siv::PerlinNoise& perlin) {
        for (auto [i, j, k] : indices_of(chunk.data())) {
            auto v = chunk.pos(i, j, k) * 0.1f;
            if (perlin.noise2D_01(v.x, v.z) * chunk::height >= j) {
                chunk.data()[i][j][k] = block::flag;
            }
        }
        chunk.generate();
    }

    terrain::terrain() {
        const siv::PerlinNoise::seed_type seed = 123456u;
        const siv::PerlinNoise perlin{ seed };


        for (auto [i, j] : indices_of(m_chunks)) {
            m_chunks[i][j].m_position = {i * 16, 0, j * 16};
            foo(m_chunks[i][j], perlin);
            continue;
            chunk& chunk = m_chunks[i][j];
            for (auto [i, j, k] : indices_of(chunk.data())) {

                if (j == 0) {
                    chunk.data()[i][j][k] = block::dirt;
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
        int x = pos.x / chunk::width;
        int z = pos.z / chunk::depth;

        if (std::abs(x - m_x) > 1 || std::abs(z - m_z) > 1) {
            center_to(x, 0, z);
        }
    }

    void terrain::center_to(int i, int j, int k) {
        for (auto [ii, jj] : indices_of(m_chunks)) {
            auto x = (i + static_cast<int>(ii) - static_cast<int>(render_distance)) * static_cast<int>(chunk::width);
            auto z = (j + static_cast<int>(jj) - static_cast<int>(render_distance)) * static_cast<int>(chunk::depth);
            m_chunks[ii][jj].m_position = glm::vec3{x, 0.0f, z};
        }
        m_position = m_chunks[0][0].m_position;
        m_x = i;
        m_z = k;
    }

}