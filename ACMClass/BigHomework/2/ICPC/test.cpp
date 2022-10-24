#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long
set <int> s;
const int N = 1e6;
int a[N + 100];

signed main() {
    
    for(int i = 0 ; i < N ; ++i){
        a[i] = rand();
        s.insert(a[i]);
    }
        
    return 0;
}