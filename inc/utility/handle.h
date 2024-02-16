/**
 * @file handle.h
 * @author Jochem Arends
 * @date 06-01-2024
 */

#include <utility>

#ifndef HANLDE_H
#define HANLDE_H

namespace ja {
    /**
     * Owns a handle to a resource.
     *
     * An owning RAII wrapper around a resource handle.
     *
     * @tparam T Type of the handle.
     * @tparam D Type of the deleter.
     */
    template<typename T, typename D>
    struct handle {
        /** 
         * Constructor.
         *
         * Constructs a new handle.
         *
         * @param resource A handle to a resource.
         * @param deleter A callable used to free the resource.
         */
        handle(T resource, D deleter = {})
            :m_resource{resource}, m_deleter{deleter} {}

        /**
         * Move constructor.
         *
         * Performs move construction.
         *
         * @param other The handle where ownership gets transferred from.
         */
        handle(handle&& other) noexcept
            :m_resource{std::move(other.m_resource)} {}

        /**
         * Move assignment.
         *
         * Performs move assignment.
         *
         * @param other The handle where ownership gets transferred from.
         */
        handle& operator=(handle&& other) noexcept {
            if (this != &other) {
                swap(other);
            }
            return *this;
        }

        handle(const handle& other) = delete;

        handle& operator=(const handle& other) = delete;

        ~handle() {
            m_deleter(m_resource);
        }


        /**
         * Swap handles.
         * 
         * Swaps the underlying resource handle with another instance.
         *
         * @param other The handle that gets swapped with.
         */
        void swap(handle& other) noexcept {
            std::swap(m_resource, other.m_resource);
        }

        /**
         * Get handle.
         *
         * Access the resource handle.
         *
         * @return The resource handle.
         */
        const T& get() const {
            return m_resource;
        }
    private:
        T m_resource{};
        D m_deleter{};
    };
}

#endif

