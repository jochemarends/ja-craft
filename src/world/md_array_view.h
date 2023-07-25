//#ifndef MD_ARRAY_VIEW_H
//#define MD_ARRAY_VIEW_H
//
//#include <iostream>
//#include <type_traits>
//#include <tuple>
//#include <span>
//#include <functional>
//
//template<std::size_t>
//struct meta_size_t {};
//
//template<typename T>
//constexpr auto end_indices(T& array) {
//    return std::make_tuple(std::extent<T>::value);
//}
//
//template<typename T>
//requires (std::rank<T>::value > 1)
//constexpr auto end_indices(T& array) {
//    auto tuple = std::make_tuple(std::extent<T>::value - 1);
//    return std::tuple_cat(tuple, end_indices(*array));
//}
//
//template<typename T>
//constexpr auto tuple_to_array(const T& tuple) {
//    auto to_array = [](const auto&... elements) {
//        return std::array{elements...};
//    };
//    return std::apply(to_array, tuple);
//}
//
//template<typename T, std::size_t N>
//constexpr auto array_to_tuple(const std::array<T, N>& array) {
//    auto to_tuple = []<std::size_t... I>(auto& array, std::index_sequence<I...>) {
//        return std::make_tuple(array[I]...);
//    };
//    return to_tuple(array, std::make_index_sequence<N>{});
//}
//
//
//auto& get(auto& array, std::size_t idx) {
//    return array[idx];
//}
//
//auto& get(auto& array, std::size_t idx, std::convertible_to<std::size_t> auto&& ...args) {
//    return get(array[idx], args...);
//}
//
//template<typename T>
//class md_array_view {
//public:
//    using size_type = std::array<std::size_t, std::rank<T>::value>;
//    using value_type = std::remove_all_extents<T>::type;
//    class iterator;
//    md_array_view(T& array);
//    iterator begin();
//    iterator end();
//private:
//    T& m_array;
//};
//
//template<typename T>
//md_array_view<T>::md_array_view(T& array)
//        :m_array{array} {}
//
//template<typename T>
//auto md_array_view<T>::begin() -> iterator {
//    return iterator{m_array};
//}
//
//template<typename T>
//auto md_array_view<T>::end() -> iterator {
//    return iterator{m_array, {std::extent<T>::value}};
//}
//
//template<typename T>
//class md_array_view<T>::iterator {
//public:
//    iterator(T& array, size_type indices = {});
//    iterator& operator++();
//    value_type& operator*();
//    bool operator==(const iterator& other) const;
//    bool operator!=(const iterator& other) const;
//    size_type operator-(const iterator& other) const;
//
//    template<std::size_t N>
//    void next(meta_size_t<N>);
//    void next(meta_size_t<0>);
//
//    T& m_array;
//    size_type m_indices;
//};
//
//template<typename T>
//md_array_view<T>::iterator::iterator(T& array, size_type indices)
//        :m_array{array}, m_indices{indices} {}
//
//template<typename T>
//auto md_array_view<T>::iterator::operator++() -> iterator& {
//    next(meta_size_t<std::rank<T>::value - 1>{});
//    return *this;
//}
//
//template<typename T>
//auto md_array_view<T>::iterator::operator*() -> value_type& {
//    auto fn = [this](auto&... args) -> value_type& {
//        return get(m_array, args...);
//    };
//    auto tuple = array_to_tuple(m_indices);
//    return std::apply(fn, tuple);
//}
//
//template<typename T>
//bool md_array_view<T>::iterator::operator==(const iterator& other) const {
//    return m_array == other.m_array && m_indices == other.m_indices;
//}
//
//template<typename T>
//bool md_array_view<T>::iterator::operator!=(const iterator& other) const {
//    return !operator==(other);
//}
//
//template<typename T>
//auto md_array_view<T>::iterator::operator-(const iterator& other) const -> size_type {
//    return size_type{};
//}
//
//template<typename T>
//template<std::size_t N>
//void md_array_view<T>::iterator::next(meta_size_t<N>) {
//    if (++m_indices[N] == std::extent<T, N>::value) {
//        m_indices[N] = 0;
//        next(meta_size_t<N - 1>{});
//    }
//}
//
//template<typename T>
//void md_array_view<T>::iterator::next(meta_size_t<0>) {
//    ++m_indices[0];
//}
//
//#endif
