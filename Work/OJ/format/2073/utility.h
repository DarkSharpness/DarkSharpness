#pragma once

#include <string>
#include <vector>
#include <utility>

namespace sjtu {

template <typename T>
decltype(auto) to_string(T &&x) {
    // remove const/volatile and reference qualifiers.
    // int &&       -> int
    // const int &  -> int
    // volatile int -> int
    using U = std::remove_cv_t <std::remove_reference_t <T>>;
    if constexpr (std::is_integral_v <U> || std::is_floating_point_v <U>) {
        return std::to_string(x);
    } else {
        return std::forward <T> (x);
    }
}

template <typename ...Args>
std::vector <std::string> make_string(Args &&...args) {
    std::vector <std::string> ret;
    ret.reserve(sizeof...(args));
    (ret.emplace_back(to_string(std::forward <Args> (args))), ...);
    return ret;
}

} // namespace sjtu
