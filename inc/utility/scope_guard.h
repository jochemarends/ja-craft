/**
 * @file scope_guard.h
 * @author Jochem Arends
 * @date 06-01-2024
 */

#ifndef SCOPE_GUARD_H
#define SCOPE_GUARD_H

#include <tuple>
#include <functional>

/**
 * A scope guard that will invoke callables on going out of scope.
 *
 * @tparam Ts The types of the callables.
 */
template<typename... Ts>
struct scope_guard {
    /**
     * Constructs a scope guard.
     * 
     * @param args The callables to invoke on going out of scope.
     */
    scope_guard(Ts... args)
        :m_callables{args...} {}

    ~scope_guard() {
        std::apply([](Ts... callables){
            (std::invoke(callables), ...);
        }, m_callables);
    }
    
    scope_guard(const scope_guard& other) = delete;

    scope_guard& operator=(const scope_guard& other) = delete;
private: 
    std::tuple<Ts...> m_callables;
};

/**
 * Creates a scope guard.
 *
 * @tparam Ts The types of the callables.
 * @param args The callables.
 * @note This function might be obsolete because since C++17, class template deduction is a thing.
 */
template<typename... Ts>
auto make_scope_guard(Ts... args) {
    return scope_guard<Ts...>{args...};
}

#endif

