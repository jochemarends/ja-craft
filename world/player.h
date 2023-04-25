#ifndef JA_PLAYER_H
#define JA_PLAYER_H

#include <glm/glm.hpp>
#include "aabb.h"

namespace ja {

    class player {
        ja::aabb aabb() const;

        void mouse_button_callback();
        void mouse_move_callback();
    private:
        glm::vec3 m_position;
    };

}

#endif
