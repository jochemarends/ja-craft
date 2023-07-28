#ifndef JA_FILE_H
#define JA_FILE_H

#include "chunk.h"

namespace ja {

    namespace file {

        void write(const ja::chunk& chunk);
        void read(ja::chunk& chunk);

    };

}

#endif
