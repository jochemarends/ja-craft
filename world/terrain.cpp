#include "terrain.h"
#include "../gfx/program.h"

namespace ja {

    terrain::terrain() {
        for (auto [i, j] : indices_of(m_chunks)) {
            for (auto k = 0; k < chunk::width; ++k) {
            //std::ranges::fill(m_chunks[i][j].m_data[k][0], 1);

            }
            m_chunks[i][j].generate();
        }
    }

    void terrain::draw() const {
//        for (auto [i, j] : indices_of(m_chunks)) {
//            glm::mat4 model{1};
//            model = glm::translate(model, glm::vec3)
//            glUniformMatrix4fv(program.uniform_location("model"), 1, GL_FALSE, glm::value_ptr(camera.view()));
//            m_chunks[i][j].m_mesh.draw();
//        }
    }

}