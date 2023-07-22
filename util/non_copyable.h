#ifndef JA_NON_COPYABLE_H
#define JA_NON_COPYABLE_H

struct non_copyable {
    non_copyable() = default;
    non_copyable(const non_copyable&) = delete;
    non_copyable& operator=(const non_copyable&) = delete;
};

#endif
