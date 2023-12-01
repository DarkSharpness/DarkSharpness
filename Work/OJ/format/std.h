#include "utility.h"
#include <stdexcept>

namespace sjtu {

struct format_error final : std::runtime_error {
    format_error() noexcept : std::runtime_error("Invalid format string!") {}
    virtual ~format_error() = default;
};

template <typename ...Args>
std::string format(std::string_view fmt, Args &&...args) {
    constexpr auto   my_assert  = [](bool cond) { if (!cond) throw format_error {}; };
    constexpr std::size_t   n   = sizeof...(args);
    constexpr std::size_t npos  = -1;

    const auto data = make_string(std::forward <Args> (args)...);
    std::string ret = {};
    std::size_t pos = {};

    for (const char *str = fmt.data() ; *str ; ++str) {
        if (*str == '{') { // Find matching '}'
            switch(*++str) {
                case '{':
                    ret.push_back('{');
                    break;
                case '}':
                    my_assert(pos < n);
                    ret += data[pos++];
                    break;

                default:
                    // pos = 0 or -1 is ok.
                    my_assert(std::isdigit(*str) && pos + 1 < 2);
                    pos = npos;
                    std::size_t idx = 0; // Index of data.
                    do { idx = idx * 10 + *(str++) - '0'; } while(std::isdigit(*str));
                    my_assert(*str == '}' && idx < n);
                    ret += data[idx];
            }
        } else {
            if (*str == '}') my_assert(*++str == '}');
            ret.push_back(*str);
        }
    }
    return ret;
}

} // namespace sjtu
