#pragma once
#include <stdexcept>
#include <functional>

namespace dark {

struct wire {
    std::function <int (void) > func;
    int operator() (void) const { return func(); }
};


struct reg {
    int value {};
    union {
        int  bak {};
        char dat[4];
    };

    int operator() (void) const { return value; }
    operator wire() { return { [this] () -> int { return value; } }; }

    void operator = (int val) { value = bak = val; }
    void operator = (reg rhs) { value = bak = rhs.value; }
    void operator <= (int val) { bak = val; }
    void operator <= (reg rhs) { bak = rhs.value; } 
    void sync() { value = bak; }

    // Set given byte to given char (indexed from 0, low byte).
    template <int l>
    requires (l >= 0 && l < 4)
    void set_byte(char val) { dat[l] = val; }
};

// Check if all the conditions are true. If not, throw.
template <typename ...T>
requires (std::convertible_to <T, bool> && ...)
inline void assert(T &&...cond) {
    if (!(bool(cond) && ...))
        throw std::runtime_error("Assertion failed");
}

/**
 * @tparam width Position of the most significant bit.
 * @param val The value to sign extend.
 * @return integer of extended value.
 */
template <int width>
requires (width >= 0 && width < 32)
inline constexpr int sign_extend(int val) {
    struct pack { int val : width + 1; };
    return pack { val }.val;
}

template <int l>
constexpr int concat_bits(int arg) { return arg; }
template <int l, int ...len>
constexpr int concat_bits(int arg, auto ...args) {
    return (arg << (len + ...)) | concat_bits <len...> (args...);
}

/**
 * @brief A class that represents serveral bits.
 * It really behaves like an wire in verilog.
 */
template <int width>
requires (width > 0 && width <= 32)
struct bits {
    using tag = bits <width>;
    int value {};

    constexpr operator int() const { return value; }

    static constexpr int length = width;
    static constexpr int mask   = width == 32 ? -1 : (1u << width) - 1;

    constexpr bits() = default;
    constexpr bits(int val) : value(val & mask) {}

    template <int ...len>
    requires (sizeof...(len) > 1 && (len + ...) == width)
    bits(bits <len> ...args) { value = concat_bits <len...> (args.value...); }
};

template <typename T>
concept bits_type = std::same_as <T, typename T::tag>;

template <typename ...T>
requires (bits_type <T> && ...)
bits(T...) -> bits <(T::length + ...)>;

/**
 * @brief Take out one or several bits from a value.
 * @tparam l Most  significant bit.
 * @tparam r Least significant bit.
 * @param val The value to take out bits from.
 * @return bits type containing extracted bits.
 */
template <int l,int r = l>
inline constexpr auto take(unsigned val) -> bits <l - r + 1> {
    static_assert(l >= r);
    return bits <l - r + 1> { int(val >> r) };
}

/**
 * @tparam width Position of the most significant bit.
 * @param val The value to sign extend.
 * @return integer of extended value.
 */
template <int width>
requires (width >= 0 && width < 32)
inline constexpr int sign_extend(bits <width> val) {
    return sign_extend <width - 1> (int(val));
}

/**
 * @brief Concatenate several bits into one.
 * @param args Bits to concatenate.
 * @return bits type containing concatenated bits.
 */
template <int ...len>
constexpr auto concat(bits <len> ...args) {
    return bits <(len + ...)> { concat_bits <len...> (int(args)...) };
}

} // namespace dark


namespace dark { // Global signals.

inline bool clock {}; // Clock signal.
inline bool reset {}; // Reset signal.
inline bool ready {}; // Ready signal.
// Not implemented wire. Throw if called.
inline const wire NotImplemented = {
    [] () -> int { throw std::runtime_error("Not implemented"); }
};


} // namespace dark
