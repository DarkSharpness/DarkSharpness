#include "int2048.cc"
#include <vector>

int main() {
    sjtu::array <int> a = {};
    sjtu::array <int> b = a;
    std::allocator <int> t;
    t.deallocate((int *)1,1);
    return 0;
}