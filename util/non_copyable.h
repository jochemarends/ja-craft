#ifndef JA_NON_COPYABLE_H
#define JA_NON_COPYABLE_H

class non_copyable {
    non_copyable(const non_copyable&) = delete;
    non_copyable& operator=(const non_copyable&) = delete;
protected:
    non_copyable() = default;
};

#endif
