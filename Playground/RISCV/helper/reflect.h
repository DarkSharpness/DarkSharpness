#pragma once
#include "hardware.h"


namespace dark {

/**
 * @brief A helper class that used to cast one type to another.
 * If you want to cast to a private member, please make this
 * class a friend of the current class.
 */
template <typename _Tp>
struct caster {
    template <typename _Vp>
    static _Vp &cast(_Tp &val) { return static_cast <_Vp &> (val); }
};
/**
 * @brief A helper class to indicate the base type to sync().
 * If you want to synchronize a base type,
 * please define tag = sync_tag <base_type>
 * @note If _Tags = void, then sync() will visit members.
 */
template <typename ..._Tags>
struct sync_tag {};

/* Forward declaration. */
template <typename _Tp>
inline void sync_member(_Tp &);
/* Forward declartion. */
template <typename _Tp>
inline void sync_base(_Tp &);


namespace detail {

template <typename _Tp>
struct is_std_array {
    static constexpr bool value = false;
};
template <typename _Tp, std::size_t _N>
struct is_std_array <std::array <_Tp, _N>> {
    static constexpr bool value = true;
};

template <typename _Tp>
struct has_sync_tag {
    static constexpr int value = 0; // Do not sync!
};
template <typename ..._Tags>
struct has_sync_tag <sync_tag <_Tags...>> {
    static constexpr int value = 1; // Visit by tags.
};
template <>
struct has_sync_tag <sync_tag <void>> {
    static constexpr int value = 2; // Visit member.
};


template <typename _Tp>
consteval int sync_type() {
    if constexpr (!requires { typename _Tp::sync; }) {
        return -1; // Unknown type, try everything.
    } else {
        return has_sync_tag <typename _Tp::sync>::value;
    }
}

template <typename _Tp> // Types with ::sync() member function.
concept syncable = requires (_Tp &t) { t.sync(); };
template <typename _Tp> // Aggregate type.
concept aggregate = std::is_aggregate_v <_Tp>;
template <typename _Tp> // std::array type.
concept std_array = is_std_array <_Tp>::value;

} // namespace detail


template <typename _Tp>
inline void synchronize(_Tp &val) {
    constexpr int value = detail::sync_type <_Tp> ();
    if constexpr (value == -1) {
        // Special case: ::sync() for directly syncable types.
        if constexpr (detail::syncable <_Tp>) val.sync();
        // Special case: We do not allow nested std::array.
        else if constexpr (detail::std_array <_Tp>) {
            // Only array of directly syncable types are allowed.
            if constexpr (detail::syncable <typename _Tp::value_type>)
                for (auto &i : val) synchronize(i);
        }
        // Speical case: aggregate type, give a try.
        else if constexpr (detail::aggregate <_Tp>) sync_member(val);
    } else if constexpr (value == 0) {
        return; // Do nothing.
    } else if constexpr (value == 1) {
        return sync_base(val);
    } else if constexpr (value == 2) {
        return sync_member(val);
    } else {
        static_assert(false, "Not supported type!");
    }
}


namespace detail {

/* A init helper to get the size of a struct. */
struct init_helper { template <typename T> operator T(); };
/* A size helper to get the size of a struct. */
template <typename T>
inline consteval std::size_t size_helper(auto &&...Args) {
    constexpr std::size_t size      = sizeof...(Args);
    constexpr std::size_t maximum   = 114;
    if constexpr (size > maximum) {
        static_assert (false, "Too many members in struct!");
    } else if constexpr (!requires {T { Args... }; }) {
        return size - 1;
    } else {
        return size_helper <T> (Args..., init_helper {});
    }
}
/**
 * @return Size of a aggregate type (struct). 
 */
template <aggregate T>
inline consteval size_t size() { return size_helper <T> (); }
/**
 * @brief Synchonize value by tag.
 * @param val Value to be synchronized.
 */
template <typename _Tp, typename _Vp, typename ..._Tags>
inline void sync_by(_Tp &val, sync_tag <_Vp, _Tags...>) {
    synchronize(caster <_Tp>::template cast <_Vp> (val));
    if constexpr (sizeof...(_Tags) > 0) sync_by <_Tp, _Tags...> (val, {});
}

} // namespace detail

/**
 * @brief Call sync() for each member of val.
 * @tparam _Tp Any type. Members no more than 12.
 */
template <typename _Tp>
inline void sync_member(_Tp &val) {
    static_assert(std::is_aggregate_v <_Tp>, "Type must be aggregate!");
    static_assert(!detail::std_array  <_Tp>, "No array allowed!");
    using namespace detail;
    constexpr auto __size = size <_Tp> ();
    constexpr auto __sync = [](auto &...args) { (synchronize(args), ...); };

    if constexpr (__size == 0) {
        // Do nothing.
    } else if constexpr (__size == 1) {
        auto &[a] = val;
        __sync(a);
    } else if constexpr (__size == 2) {
        auto &[a, b] = val;
        __sync(a, b);
    } else if constexpr (__size == 3) {
        auto &[a, b, c] = val;
        __sync(a, b, c);
    } else if constexpr (__size == 4) {
        auto &[a, b, c, d] = val;
        __sync(a, b, c, d);
    } else if constexpr (__size == 5) {
        auto &[a, b, c, d, e] = val;
        __sync(a, b, c, d, e);
    } else if constexpr (__size == 6) {
        auto &[a, b, c, d, e, f] = val;
        __sync(a, b, c, d, e, f);
    } else if constexpr (__size == 7) {
        auto &[a, b, c, d, e, f, g] = val;
        __sync(a, b, c, d, e, f, g);
    } else if constexpr (__size == 8) {
        auto &[a, b, c, d, e, f, g, h] = val;
        __sync(a, b, c, d, e, f, g, h);
    } else if constexpr (__size == 9) {
        auto &[a, b, c, d, e, f, g, h, i] = val;
        __sync(a, b, c, d, e, f, g, h, i);
    } else if constexpr (__size == 10) {
        auto &[a, b, c, d, e, f, g, h, i, j] = val;
        __sync(a, b, c, d, e, f, g, h, i, j);
    } else if constexpr (__size == 11) {
        auto &[a, b, c, d, e, f, g, h, i, j, k] = val;
        __sync(a, b, c, d, e, f, g, h, i, j, k);
    } else if constexpr (__size == 12) {
        auto &[a, b, c, d, e, f, g, h, i, j, k, l] = val;
        __sync(a, b, c, d, e, f, g, h, i, j, k, l);
    } else {
        static_assert(false, "Too many members in struct!");
    }
}

/**
 * @brief Call sync() for each base type of val.
 * @tparam _Tp Any type. Base members no more than 12.
 */
template <typename _Tp>
inline void sync_base(_Tp &val) { return detail::sync_by(val, typename _Tp::sync {}); }

} // namespace dark
