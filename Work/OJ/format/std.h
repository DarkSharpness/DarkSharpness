#include "utility.h"
#include <stdexcept>

namespace sjtu {

void my_assert(bool cond, const char *msg) {
    if (!cond) throw std::runtime_error(msg);
}

template <typename ...Args>
std::string format(std::string_view fmt, Args &&...args) {
    constexpr std::size_t   n   = sizeof...(args);
    constexpr std::size_t npos  = -1;

    const auto data = make_string(std::forward <Args> (args)...);
    std::string ret = {};
    std::size_t pos = {};

    for (const char *str = fmt.data() ; *str ; ++str) {
        if (*str == '{') {
            switch(*++str) {
                case '{':
                    ret.push_back('{');
                    break;

                case '}':
                    my_assert(pos < n, "Invalid format string!");
                    ret += data[pos++];
                    break;

                default:
                    // pos = 0 or -1 is ok.
                    my_assert(std::isdigit(*str) && pos + 1 < 2, "Invalid format string!");
                    pos = npos;

                    std::size_t idx = 0; // Index of data.
                    while(std::isdigit(*str)) { idx = idx * 10 + *(str++) - '0'; }
                    my_assert(*str == '}' && idx < n, "Invalid format string!");
                    ret += data[idx];
            }
        } else {
            if (*str == '}')
                my_assert(*++str == '}', "Invalid format string!");
            ret.push_back(*str);
        }
    }

    return ret;
}

} // namespace sjtu
