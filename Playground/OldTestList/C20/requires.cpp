#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

template <class T>
concept cleaner = requires (vector <T> a) { a.clear(); };

template <cleaner T>
void clean(T &x) { x.clear(); }



signed main() {
    std::vector <int> v = {3,4,5,6,7};
    dark::writelineRange(v.begin(),v.end());
    clean(v);
    dark::writelineRange(v.begin(),v.end());
    return 0;
}