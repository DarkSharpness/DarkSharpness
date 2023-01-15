#include <Dark/any>
#include <iostream>

signed main() {
    dark::Any x;
    if(x.is <int> ()) std::cout << "int";
    else {
        x = 1;
        std::cout << int(x);
    }
    return 0;
}