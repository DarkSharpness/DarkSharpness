#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long

int f[42][42][42][42];
int n,m;
int cnt[5];
int a[400];
constexpr int N = pow(41,4);
int pre[N][4];

signed main() {
    scanf("%d%d",&n,&m);
    for(int i = 1 ; i <= n ; ++i) scanf("%d",&a[i]);
    for(int i = 1,x; i <= m ; ++i) 
        scanf("%d",&x),++cnt[x];
    for(int i = 1 ; i <= cnt[1] ; ++i) 
        for(int j = 1; j <= cnt[2] ; ++j)
            for(int k = 1 ; k <= cnt[3] ; ++k)
                for(int l = 1; l <= cnt[4] ; ++k) {
                    if(i != cnt[1]);
                    

                }
    return 0;
}