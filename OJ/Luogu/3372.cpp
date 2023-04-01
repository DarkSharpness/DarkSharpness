/*
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e5 + 4;
int v[N];

//非递归形式
struct segmentTree {
    int M;
    struct node{
        ll tag;
        //int mxn;
        ll val;
        node() {
            val = tag = 0;
        }
    }t[N<<2];
    inline void pushup(int id) {
        t[id].val = t[id<<1].val + t[id<<1|1].val;
    }
    inline void build(int n){
        M = 1 ;
        while(M < n) M <<= 1; //最后M>=n
        for(int i = 0 ; i < n; ++i)
            t[N|i].val = v[i];
        for(int i = N-1; i ; --i)
            pushup(i);
    }
    inline void update(int l,int r,ll val) {
        l += N-1;
        r += N-1;
        int counter = 1;
        while(l!=r) {

        }   
    }

}T;


int main() {

    return 0;
}
*/