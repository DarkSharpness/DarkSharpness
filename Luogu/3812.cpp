#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


const int N = 51;
int n;
ll a[N];//线性基
int cnt = N;
inline bool insert_base(ll x) { //插入线性基
    for(int i = cnt ; i != -1 ; --i) {
        if(x & (1ll << i)) {
            if(!a[i]) {   //还不能表示,
                a[i] = x; 
                return true;
            } else {     //已经能表示了
                x ^= a[i];
            }
        }
    }
    return false;//xor till 0
}


int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        insert_base(a[i]);
    }
    
    return 0;
}