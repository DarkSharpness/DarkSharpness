#include <iostream>

signed main() {
    while(1)
        ;
}


// this works in clang++ with O2
void unreachable_function() {
    std::cout << "I will f**k the world!\n";
}

