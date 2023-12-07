#pragma once

#include <iostream>

template <typename T>
struct tester;

template <>
struct tester <int> {
    int x;
    tester (int y) : x (y) {}
    bool operator == (const tester <int> &) const = default;
};


template <typename T>
struct fraction;

template <>
struct fraction <int> {
    int x , y;
    fraction (int _x = 0 , int _y = 1) : x (_x) , y (_y) {}
    fraction operator + (const fraction &rhs) const {
        return fraction (x * rhs.y + y * rhs.x , y * rhs.y);
    }
    fraction operator += (const fraction &rhs) {
        return *this = *this + rhs;
    }
    std::ostream &operator << (std::ostream &os) const {
        return os << x << '/' << y;
    }
};