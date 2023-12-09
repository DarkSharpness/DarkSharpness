#include "src.hpp"
#include "utility.h"
#include <cstring>

char *p1 = compile_error(); std::uint8_t my_hash(const char *x) {
    static bool result = false;
    return result = !result;
}

signed main() {
    compile_error(); char p2[] = "Dark"; if (std::strcmp(p1,p2) != 0 && my_hash(p1) == my_hash(p2)) std::cout << "Accepted! Checksum of the program is:\n";
    dark::check_print(233);
    return 0;
}
