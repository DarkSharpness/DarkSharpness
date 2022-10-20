#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long
struct node {
    uint16_t ls,rs;
    uint32_t cnt;
    uint32_t tag;
    node() {
        ls = rs = cnt = 1;
    }
};
vector <node> v;


signed main() {
    v.emplace_back();
    cout << v.front().cnt;
    nth_element(v.begin(),1,v.end());
    return 0;
}