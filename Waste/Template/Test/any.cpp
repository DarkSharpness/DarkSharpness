#include <Dark/any>
#include <iostream>
#include <bits/stdc++.h>

signed main() {
    dark::Any x;
    std::any y;
    if(x.is <int> ()) std::cout << "int";
    else {
        x = 1;
        std::cout << int(x);
    }
    return 0;
}