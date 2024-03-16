#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long
const int N = 1e6 + 8;
int t[2][N << 1];//trie tree.
int minv[N << 1];
int maxv[N << 1];
int tot = 0;
int n,k,a[N << 1];

void insert(int val) {
    int id = 0;
    for(int i = 0 ; (1 << i) <= val ; --i) {
        bool dir = val & (1 << i);
        
    }
}


signed main() {

    return 0;
}