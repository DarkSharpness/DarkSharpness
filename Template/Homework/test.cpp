#include <bits/stdc++.h>
// #include <Dark/inout>
// #define int long long
// using ll = long long;
// using ull = unsigned long long;
using namespace std;

struct node { int x; };

signed main() {
    pair <int,node> t[2];
    t[0].first = 1;
    t[1].first = 2;
    std::cout << (t[0] < t[1]);

    return 0;
}