#include <bits/stdc++.h>
#include <Dark/inout>

void func(std::string_view str) {
    std::cout << str << ' ' << str.size() << '\n';
}


signed main() {
    std::string_view str("abcdef",3);
    std::string_view hastin = "Hastin is my best friend.";
    func(str);
    func(hastin);               // Constant time. 
    func({"darksharpness",3});  // Constant time.
    func("apachiww");           // Time cost from strlen().
    // {"str",3};
    return 0;
}