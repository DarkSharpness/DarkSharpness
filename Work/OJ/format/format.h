#include "utility.h"
#include <stdexcept>

namespace sjtu {

template <typename ...Args>
std::string format(std::string_view fmt, Args &&...args);

} // namespace sjtu
