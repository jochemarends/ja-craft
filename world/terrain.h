#ifndef JA_TERRAIN_H
#define JA_TERRAIN_H

#include "chunk.h"

namespace ja {

    class terrain {
    public:
        terrain();
        void draw() const;
        chunk m_chunks[4][4];
    private:
    };

}

#endif
