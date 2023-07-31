// #include <bits/stdc++.h>
#include <format>
#include <iostream>
#include <vector>



signed main() {
    std::string tmp = std::format("{1}{1}{0}!", "810", 19);
    std::cout << tmp << std::endl;

    std::string str = "This is a string";
    std::cout << str.starts_with("This") << ' '
              << sizeof(int *) << '\n';
    std::vector a{1,2,3,4,5};
    for(const auto &x : a)
        std::cout<< std::format("Value: {}\n",x); //


    return 0;
}