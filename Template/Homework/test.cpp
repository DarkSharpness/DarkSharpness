#include <bits/stdc++.h>
// #include <Dark/inout>
// #define int long long
// using ll = long long;
// using ull = unsigned long long;
using namespace std;

class node {
    int x,y;
  public:
    node(int a,int b) : x(a),y(b) {}
    int values() { return x + y; }
};

node func() {
    return {1,2};
}

signed main() {
    cout << func().values();

    return 0;
}