#ifndef JA_OPTIONAL_REF_H
#define JA_OPTIONAL_REF_H

#include <optionaL>

namespace ja {

    template<typename T>
    struct optional_ref {
        friend bool operator==(optional_ref<T> lhs, optional_ref<T> rhs);
        friend bool operator!=(optional_ref<T> lhs, optional_ref<T> rhs);

        // construction
        optional_ref(T& value);
        optional_ref(std::nullopt_t);
        optional_ref(const optional_ref& other);

        // assignment
        optional_ref& operator=(T& value);
        optional_ref& operator=(std::nullopt_t);
        optional_ref& operator=(const optional_ref& other);

        // observers
        operator bool() const;
        bool has_value() const;

        T& value() const;

        T* operator->() const;
        T& operator*() const;

        // modifiers
        void reset();
    private:
        T* m_ptr;
    };

    template<typename T>
    optional_ref<T>::optional_ref(T& value)
        :m_ptr{&value} {}

    template<typename T>
    optional_ref<T>::optional_ref(std::nullopt_t)
        :m_ptr{nullptr} {}

    template<typename T>
    optional_ref<T>::optional_ref(const optional_ref<T>& other)
        :m_ptr{other.m_ptr} {}

    template<typename T>
    optional_ref<T>& optional_ref<T>::operator=(T& value) {
        m_ptr = &value;
    }

    template<typename T>
    optional_ref<T>& optional_ref<T>::operator=(std::nullopt_t) {
        m_ptr = nullptr;
    }

    template<typename T>
    optional_ref<T>& optional_ref<T>::operator=(const optional_ref<T>& other) {
        m_ptr = other.m_ptr;
    }

    template<typename T>
    optional_ref<T>::operator bool() const {
        return has_value();
    }

    template<typename T>
    bool optional_ref<T>::has_value() const {
        return m_ptr != nullptr;
    }

    template<typename T>
    T& optional_ref<T>::value() const {
        if (!has_value()) throw std::bad_optional_access{};
        return *m_ptr;
    }

    template<typename T>
    T* optional_ref<T>::operator->() const {
        return m_ptr;
    }

    template<typename T>
    T& optional_ref<T>::operator*() const {
        return *m_ptr;
    }

    template<typename T>
    void optional_ref<T>::reset() {
        m_ptr = nullptr;
    }

    template<typename T>
    bool operator==(optional_ref<T> lhs, optional_ref<T> rhs) {
        return lhs.m_ptr == rhs.m_ptr;
    }

    template<typename T>
    bool operator!=(optional_ref<T> lhs, optional_ref<T> rhs) {
        return !(lhs == rhs);
    }

}

#endif
