#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long

void f(int && t) {
    puts("R");
}
void f(int & t) {
    puts("L");
}


template <typename T>
void emplace(T && t) {
    f(forward <T>(t));
}



signed main() {
    int n = 5;
    emplace(n+1);
    vector<int> v {1,2,3};
    return 0;
}