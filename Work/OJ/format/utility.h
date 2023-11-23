#include <string>
#include <vector>
#include <utility>

namespace sjtu {

template <typename T>
decltype(auto) to_string(T &&x) {
    if constexpr (std::is_integral_v <T> || std::is_floating_point_v <T>) {
        return std::to_string(std::forward <T> (x));
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
