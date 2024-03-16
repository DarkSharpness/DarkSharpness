#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
//#define int lont long

inline void debugPrint() {std::cout<<'\n';}

template <class T,class ...V>
void debugPrint(const T &arg,const V &...args) {
    std::cout << arg << ' ';
    debugPrint(args...);
}


int main() {
    std::string str("test message");
    debugPrint("Hello, Happy World!", 19260817, false, str);
    debugPrint("debug");
    return 0;
}