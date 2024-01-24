#pragma once
#include <iostream>

// Output for int2048 type.
std::ostream & operator << (std::ostream &os, __int128_t x) {
    if (!x) return os << '0';
    if (x < 0) { os << '-'; x = -x; }
    char    buf[40];
    char *  top = buf + 39;
    *top = '\0';
    while(x) {
        *--top = (x % 10) | '0';
        x /= 10;
    }
    return os << top;
}

#include "src.hpp"

/* Reproducable random function. */
std::size_t my_rand() {
    static_assert(sizeof(std::size_t) == 8);
    static std::size_t seed = 1919810 ^ 114514;
    return seed = ((seed ^ std::size_t{1919810}) * std::size_t{415}) ^ (seed >> 14) ^ std::size_t{1};
}

#include <concepts>

template <typename _Tp, typename _Frac>
concept well_defined = requires(_Tp x, _Frac y, _Frac z) {
    _Frac {};    // default constructor
    _Frac {x};   // constructor with one argument
    _Frac {x,x}; // constructor with two arguments
    _Frac {y};   // copy constructor
    _Frac {std::move(y)};   // move constructor
    y = z;                  // copy assignment
    z = std::move(y);       // move assignment
    { -y } -> std::same_as <_Frac>; // unary minus
    { ~y } -> std::same_as <_Frac>; // unary inverse
    { y + y } -> std::same_as <_Frac>; // binary plus
    { y - y } -> std::same_as <_Frac>; // binary minus
    { y * y } -> std::same_as <_Frac>; // binary multiply
    { y / y } -> std::same_as <_Frac>; // binary divide
    { y += y } -> std::same_as <_Frac &>; // compound plus
    { y -= y } -> std::same_as <_Frac &>; // compound minus
    { y *= y } -> std::same_as <_Frac &>; // compound multiply
    { y /= y } -> std::same_as <_Frac &>; // compound divide
    { static_cast<double>(y)    } -> std::same_as<double>;  // cast to double
    { static_cast<bool>(y)      } -> std::same_as<bool>;    // cast to bool
    { y == y }  -> std::same_as<bool>; // equal
    { y < y  }  -> std::same_as<bool>; // less
    { std::cout << y } -> std::same_as<std::ostream &>; // output
};

// Left unimplemented to give a compile-time error. 
void Some_of_your_member_functions_are_missing();

template <void *>
struct anti_hacker { template <class _Tp> using frac = fraction <_Tp>; };

template <typename _Tester>
void anti_hack() {
    if constexpr (well_defined <int, fraction<int>>) {
        _Tester {} ();
    } else {
        Some_of_your_member_functions_are_missing();
    }
}
