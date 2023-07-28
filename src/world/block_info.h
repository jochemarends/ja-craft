#ifndef JA_CRAFT_BLOCK_INFO_H
#define JA_CRAFT_BLOCK_INFO_H

#include "chunk.h"

namespace ja {

    template<typename T>
    concept chunk_type = std::same_as<ja::chunk, std::remove_cv_t<T>>;

    template<chunk_type Chunk>
    struct block_info {
        block_info(Chunk& chunk, glm::ivec3 index);

        const ja::chunk& chunk() const;
        ja::chunk& chunk();

        glm::ivec3 index() const;

        const ja::block& value() const;
        ja::block& value();

        ja::aabb aabb() const;
    private:
        std::reference_wrapper<Chunk> m_chunk;
        glm::ivec3 m_index;
    };

    template<chunk_type Chunk>
    block_info<Chunk>::block_info(Chunk& chunk, glm::ivec3 index)
            :m_chunk{chunk}, m_index{index} {}

    template<chunk_type Chunk>
    const ja::chunk& block_info<Chunk>::chunk() const {
        return m_chunk;
    }

    template<chunk_type Chunk>
    ja::chunk& block_info<Chunk>::chunk() {
        return m_chunk;
    }

    template<chunk_type Chunk>
    glm::ivec3 block_info<Chunk>::index() const {
        return m_index;
    }

    template<chunk_type  Chunk>
    const ja::block& block_info<Chunk>::value() const {
        return m_chunk.get().data()[m_index.x][m_index.y][m_index.z];
    }

    template<chunk_type Chunk>
    ja::block& block_info<Chunk>::value() {
        return m_chunk.get().data()[m_index.x][m_index.y][m_index.z];
    }

    template<chunk_type Chunk>
    ja::aabb block_info<Chunk>::aabb() const {
        return m_chunk.get().aabb(m_index.x, m_index.y, m_index.z);
    }
}

#endif
