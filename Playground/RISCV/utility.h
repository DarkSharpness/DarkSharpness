#pragma once
#include <stdexcept>
#include <functional>

namespace dark {

inline bool clock {};
inline bool reset {};
inline bool ready {};

struct wire {
    std::function <int (void) > func;
    int operator() ()  { return func(); }
};

struct reg {
    int value {};
    union {
        int  bak {};
        char dat[4];
    };

    int operator() ()  { return value; }
    operator wire() { return { [this] () -> int { return value; } }; }

    void operator = (int val) { value = bak = val; }
    void operator = (reg rhs) { value = bak = rhs.value; }
    void operator <= (int val) { bak = val; }
    void operator <= (reg rhs) { bak = rhs.value; } 
    void sync() { value = bak; }

    template <int l>
    void set_byte(char val) {
        static_assert(l >= 0 && l < 4);
        dat[l] = val;
    }
};

template <int l,int r = l>
constexpr int take(int val) {
    static_assert(l >= r);
    constexpr int width = l - r + 1;
    if constexpr (width == 32) {
        return val;
    } else {
        unsigned tmp = val;
        return (tmp >> r) & ((1u << width) - 1);
    }
}

inline const wire NotImplemented = { [] () -> int { throw std::runtime_error("Not implemented"); } };


// Check if all the conditions are true.
template <typename ...T>
requires (std::convertible_to <T, bool> && ...)
inline void assert(T &&...cond) {
    if (!(bool(cond) && ...))
        throw std::runtime_error("Assertion failed");
}

} // namespace dark
