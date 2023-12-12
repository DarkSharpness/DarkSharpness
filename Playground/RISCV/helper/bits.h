#pragma once
#include <concepts>

/* Implementation of bits type and bits operation. */
namespace dark {
namespace detail {

template <int l>
constexpr int concat_bits(int arg) { return arg; }
template <int l, int ...len>
constexpr int concat_bits(int arg, auto ...args) {
    return (arg << (len + ...)) | concat_bits <len...> (args...);
}

struct bits_tag {};

} // namespace detail

template <typename T>
concept bits_type = std::same_as <detail::bits_tag, typename T::tag>;

/**
 * @brief A class that represents serveral bits.
 * It really behaves like an wire in verilog.
 */
template <int width>
struct bits {
    static_assert(width > 0 && width <= 32);
    using tag = detail::bits_tag;
    int value {};

    constexpr operator int() const { return value; }

    static constexpr int length = width;
    static constexpr int mask   = width == 32 ? -1 : (1u << width) - 1;

    constexpr bits() = default;
    constexpr bits(int val) : value(val & mask) {}

    template <int ...len>
    requires (sizeof...(len) > 1 && (len + ...) == width)
    bits(bits <len> ...args) { value = detail::concat_bits <len...> (args.value...); }
};


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
inline constexpr int sign_extend(int val) {
    struct pack { int val : width + 1; };
    return pack { val }.val;
}


/**
 * @tparam width Position of the most significant bit.
 * @param val The value to sign extend.
 * @return integer of extended value.
 */
template <int width>
requires (width > 0 && width <= 32)
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
