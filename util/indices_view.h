#ifndef JA_CRAFT_INDICES_VIEW_H
#define JA_CRAFT_INDICES_VIEW_H

#include <tuple>

template<std::size_t>
struct meta_size_t {};

template<typename T>
constexpr auto tuple_to_array(const T& tuple) {
    auto to_array = [](const auto&... elements) {
        return std::array{elements...};
    };
    return std::apply(to_array, tuple);
}

template<typename T, std::size_t N>
constexpr auto array_to_tuple(const std::array<T, N>& array) {
    auto to_tuple = []<std::size_t... I>(auto& array, std::index_sequence<I...>) {
        return std::make_tuple(array[I]...);
    };
    return to_tuple(array, std::make_index_sequence<N>{});
}

template<typename T, std::size_t N, typename... Ts>
struct tuple_of_n;

template<typename T, typename... Ts>
struct tuple_of_n<T, 0, Ts...> {
    using type = std::tuple<Ts...>;
};

template<typename T, std::size_t N, typename... Ts>
struct tuple_of_n {
    using type = tuple_of_n<T, N - 1, Ts..., T>::type;
};

template<typename T>
class indices_view {
public:
    using size_type = std::size_t;
    using index_type = tuple_of_n<std::size_t, std::rank<T>::value>::type;
    using value_type = std::remove_all_extents<T>::type;
    class iterator;
    indices_view(T& array);
    iterator begin();
    iterator end();
private:
    T& m_array;
};

template<typename T>
indices_view<T>::indices_view(T& array)
    :m_array{array} {}

template<typename T>
auto indices_view<T>::begin() -> iterator {
    return iterator{};
}

template<typename T>
auto indices_view<T>::end() -> iterator {
    index_type idx{};
    std::get<0>(idx) = std::extent<T>::value;
    return iterator{idx};
}

template<typename T>
class indices_view<T>::iterator {
public:
    iterator(index_type indices = {});
    iterator& operator++();
    index_type& operator*();
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
private:
    template<std::size_t N>
    void next(meta_size_t<N>);
    void next(meta_size_t<0>);
    index_type m_indices;
};

template<typename T>
indices_view<T>::iterator::iterator(index_type indices)
    :m_indices{indices} {}

template<typename T>
auto indices_view<T>::iterator::operator++() -> iterator& {
    next(meta_size_t<std::rank<T>::value - 1>{});
    return *this;
}

template<typename T>
auto indices_view<T>::iterator::operator*() -> index_type& {
    return m_indices;
}

template<typename T>
bool indices_view<T>::iterator::operator==(const iterator& other) const {
    return m_indices == other.m_indices;
}

template<typename T>
bool indices_view<T>::iterator::operator!=(const iterator& other) const {
    return !operator==(other);
}

template<typename T>
template<std::size_t N>
void indices_view<T>::iterator::next(meta_size_t<N>) {
    if (++std::get<N>(m_indices) == std::extent<T, N>::value) {
        std::get<N>(m_indices) = 0;
        next(meta_size_t<N - 1>{});
    }
}

template<typename T>
void indices_view<T>::iterator::next(meta_size_t<0>) {
    ++std::get<0>(m_indices);
}

template<typename T>
auto indices_of(const T& array) {
    return indices_view{array};
}

#endif
