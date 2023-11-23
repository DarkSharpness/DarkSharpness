#include "utility.h"
#include <stdexcept>

namespace sjtu {

void my_assert(bool cond, const char *msg) {
    if (!cond) throw std::runtime_error(msg);
}

template <typename ...Args>
std::string format(std::string fmt, Args &&...args) {
    constexpr std::size_t n = sizeof...(args);

    std::string ret = {};
    const auto data = make_string(std::forward <Args> (args)...);
    std::size_t pos = 0;

    const char *str = fmt.c_str();

    while(*str) {
        if (*str == '{') {
            switch(*++str) {
                case '{': ret.push_back('{'); break;
                case '}':
                    my_assert(pos < n, "Invalid format string!");
                    ret += data[pos++];
                    break;
                default:
                    pos = std::size_t(-1);
                    std::size_t idx = 0;
                    while(std::isdigit(fmt[i])) { idx = idx * 10 + fmt[i++] - '0'; }
                    my_assert(fmt[i] == '}' && idx < n, "Invalid format string!");
            }

            ret += data[idx];
        } else {
            
            ret.push_back(*str);
        }
    }
    return ret;
}

} // namespace sjtu
