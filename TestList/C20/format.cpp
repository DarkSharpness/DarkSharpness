// #include <bits/stdc++.h>
#include <format>
#include <iostream>
#include <vector>

signed main() {
    std::cout << std::format("{}\n",10);
    std::string str = "This is a string";
    std::cout << str.starts_with("This") << ' '
              << sizeof(int *) << '\n';
    std::vector a{1,2,3,4,5};
    for(const auto &x : a)
        std::cout<< std::format("Value: {}\n",x);
    return 0;
}