#include "chunk.h"
#include <algorithm>
#include <functional>
#include "mesh.h"
#include <iostream>
#include <ranges>

namespace ja {
    chunk::chunk() {
        for (auto [i, j, k] : indices_of(m_data)) {
            if (i == 0 && j == 0 && k == 0) continue;
            m_data[i][j][k] = block::empty;
        }
    }
}

template<int N>
auto projection(const std::ranges::input_range auto& range, ja::chunk& chunk, int i, int j, int k) {
    return std::views::transform(range, [&](auto vertex) {
        vertex.position += glm::vec3{i, j, k};
        vertex.texcoord.z = ja::texture_indices[chunk.m_data[i][j][k]][N];
        return vertex;
    });
}

void ja::chunk::generate() {
    m_mesh.clear();

    for (auto [i, j, k] : indices_view{m_data}) {
        if (m_data[i][j][k] == block::empty) continue;

        auto move_vertex = [&, this, offset = glm::vec3{i, j, k}](auto vertex) {
            vertex.position += offset;
            vertex.texcoord.z = texture_indices[m_data[i][j][k]][0];
            return vertex;
        };


        // front face
        m_mesh.add_indices(indices, m_mesh.vertices().size());
        m_mesh.add_vertices(projection<0>(front, *this, i, j, k));

        // back face
        m_mesh.add_indices(indices, m_mesh.vertices().size());
        m_mesh.add_vertices(projection<1>(back, *this, i, j, k));

        // left face
        m_mesh.add_indices(indices, m_mesh.vertices().size());
        m_mesh.add_vertices(projection<2>(left, *this, i, j, k));

        // right face
        m_mesh.add_indices(indices, m_mesh.vertices().size());
        m_mesh.add_vertices(projection<3>(right, *this, i, j, k));

        // top face
        m_mesh.add_indices(indices, m_mesh.vertices().size());
        m_mesh.add_vertices(projection<4>(top, *this, i, j, k));

        // bottom face
        m_mesh.add_indices(indices, m_mesh.vertices().size());
        m_mesh.add_vertices(projection<5>(bottom, *this, i, j, k));
    }

    m_mesh.update_buffers();
}

auto ja::chunk::data() const -> const data_type& {
    return m_data;
}

auto ja::chunk::data() -> data_type& {
    return m_data;
}

//auto ja::chunk::test(ja::ray ray) const -> std::optional<std::pair<tuple_of_n_impl<std::size_t, 3>::type, ja::face>> {
//    using index_type = tuple_of_n_impl<std::size_t, 3>::type;
//    using result_type = std::optional<std::pair<index_type, face>>;
//
//    result_type min;
//
//    auto to_vec3 = [](const auto& tuple) {
//        auto& [i, j, k] = tuple;
//        return glm::vec3{i, j, k};
//    };
//
//    auto pred = [&](auto i, auto j, auto k) {
//        if (!min) return true;
//        float d1 = glm::distance(ray.origin, pos(i, j, k));
//        auto [x, y, z] = min->first;
//        float d2 = glm::distance(ray.origin, pos(x, y, z));
//        return d1 < d2;
//    };
//
//    for (auto [i, j, k] : indices_view{m_data}) {
//        if (m_data[i][j][k] == block::empty) continue;
//
////        ja::aabb aabb{
////            .min{-0.5 + i, -0.5 + j, -0.5 + k},
////            .max{ 0.5 + i,  0.5 + j,  0.5 + k}
////        };
//        ja::aabb aabb = this->aabb(i, j, k);
//        auto hit_face = ja::test(ray, aabb);
//        if (hit_face && pred(i, j, k)) {
//            min = std::make_pair(std::make_tuple(i, j, k), *hit_face);
//        }
//    }
//
//    return min;
//}

ja::aabb ja::chunk::aabb(std::size_t i, std::size_t j, std::size_t k) const {
    ja::aabb res{
        .min{-0.5 + i, -0.5 + j, -0.5 + k},
        .max{ 0.5 + i,  0.5 + j,  0.5 + k}
    };
    res.min += m_position;
    res.max += m_position;
    return res;
}

ja::aabb ja::chunk::aabb() const {
    ja::aabb res{
        .min{-0.5f,                 -0.5f,        -0.5f},
        .max{ width - 0.5f, height - 0.5f, depth - 0.5f}
    };
    res.min += m_position;
    res.max += m_position;
    return res;
}

glm::vec3 ja::chunk::pos(std::size_t i, std::size_t j, std::size_t k) const {
    return glm::vec3{i, j, k} + m_position;
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
