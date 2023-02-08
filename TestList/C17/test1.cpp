#include <bits/stdc++.h>
#include <Dark/inout>


struct MyStruct {
    int id;
    std::string name;
} ms;

signed main() {
    auto  [id,name] = MyStruct{};
    auto &[x,y] = ms;
    dark::writeline(ms.id);
    x = 114514;
    dark::writeline(ms.id);
    return 0;
}