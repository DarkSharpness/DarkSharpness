#include "1048.hpp"


void hello() {
    std::cout << "Hello world!" << std::endl;
}

int main()
{
    int *p = new int [2];
    // auto ptr = [&](){delete [] p;};
    Defer defer([&](){delete [] p;});
    defer([&](){std::cout << p[0] << " " << p[1] << std::endl;});
    defer([&](){p[0] = 0, p[1] = 1;});
    defer(hello);
    // auto ptr = hello;
    p[0] = 2, p[1] = 3;
    return 0;
}