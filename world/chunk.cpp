#include "chunk.h"
#include <algorithm>
#include <functional>
#include "mesh.h"
#include <iostream>

namespace ja {
    chunk::chunk() {
        for (auto [i, j, k] : indices_of(m_data)) {
            if (i == 0 && j == 0 && k == 0) continue;
            m_data[i][j][k] = block::empty;
        }
    }
}
void ja::chunk::generate() {
    m_mesh.clear();

    for (auto [i, j, k] : indices_view{m_data}) {
        if (m_data[i][j][k] == block::empty) continue;

        auto move_vertex = [&, this, offset = glm::vec3{i, j, k}](auto vertex) {
            vertex.position += offset;
            vertex.texcoord.z = static_cast<float>(m_data[i][j][k]);
            return vertex;
        };

        // front face
        m_mesh.add_indices(indices, m_mesh.vertices().size());
        m_mesh.add_vertices(front, move_vertex);

        // back face
        m_mesh.add_indices(indices, m_mesh.vertices().size());
        m_mesh.add_vertices(back, move_vertex);

        // left face
        m_mesh.add_indices(indices, m_mesh.vertices().size());
        m_mesh.add_vertices(left, move_vertex);

        // right face
        m_mesh.add_indices(indices, m_mesh.vertices().size());
        m_mesh.add_vertices(right, move_vertex);

        // top face
        m_mesh.add_indices(indices, m_mesh.vertices().size());
        m_mesh.add_vertices(top, move_vertex);

        // bottom face
        m_mesh.add_indices(indices, m_mesh.vertices().size());
        m_mesh.add_vertices(bottom, move_vertex);
    }

    m_mesh.update_buffers();
}

auto ja::chunk::data() -> data_type& {
    return m_data;
}

auto ja::chunk::test(ja::ray ray) const -> std::optional<std::pair<tuple_of_n<std::size_t, 3>::type, ja::face>> {
    using index_type = tuple_of_n<std::size_t, 3>::type;
    using result_type = std::optional<std::pair<index_type, face>>;

    result_type min;

    auto to_vec3 = [](const auto& tuple) {
        auto& [i, j, k] = tuple;
        return glm::vec3{i, j, k};
    };

    auto pred = [&](auto i, auto j, auto k) {
        if (!min) return true;
        float d1 = glm::distance(ray.origin, {i, j, k});
        float d2 = glm::distance(ray.origin, to_vec3(min->first));
        return d1 < d2;
    };

    for (auto [i, j, k] : indices_view{m_data}) {
        if (m_data[i][j][k] == block::empty) continue;

        ja::aabb aabb{
            .min{-0.5 + i, -0.5 + j, -0.5 + k},
            .max{ 0.5 + i,  0.5 + j,  0.5 + k}
        };

        auto hit_face = ja::test(ray, aabb);
        if (hit_face && pred(i, j, k)) {
            min = std::make_pair(std::make_tuple(i, j, k), *hit_face);
        }
    }

    return min;
}

ja::aabb ja::chunk::aabb(std::size_t i, std::size_t j, std::size_t k) const {
    return ja::aabb{
        .min{-0.5 + i, -0.5 + j, -0.5 + k},
        .max{ 0.5 + i,  0.5 + j,  0.5 + k}
    };
}

ja::chunk::iterator::iterator(const chunk& chunk, glm::uvec3 idx) : m_chunk{chunk}, m_idx{idx} {}

glm::vec3 ja::chunk::iterator::position() const {
    return m_idx;
}

glm::uvec3 ja::chunk::iterator::index() const {
    return m_idx;
}

ja::aabb ja::chunk::iterator::aabb() const {
    return ja::aabb{
        .min{-0.5 + m_idx.x, -0.5 + m_idx.y, -0.5 + m_idx.z},
        .max{ 0.5 + m_idx.x,  0.5 + m_idx.y,  0.5 + m_idx.z}
    };
}