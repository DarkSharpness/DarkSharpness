#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4e4 + 8;
int anc[N];

vector <int> sz(N,1);
int Find(int x) {
    if(anc[x] == x) return x;
    else return anc[x] = Find(anc[x]);
}

inline void merge(int x,int y) {
    int xx = Find(x),
        yy = Find(y);
    if(xx == yy) return ;
    if(sz[xx] > sz[yy]) swap(xx,yy);
    anc[xx] = yy;
    sz[yy] += sz[xx];
}


int col[N];
int val[N]; //价值val = 体积unit
int cnt = 0;


inline void compress(int unit,int SZ){
    int i = 1;
    cnt = 0;
    while(SZ > i){
        SZ -= i;
        val[++cnt] = unit * i;
        i <<= 1;
    }
    val[++cnt] = unit*SZ;
}

bitset <N> vis;
bitset <N> dp;

int main() {
    int n,m,k;
    ios::sync_with_stdio(false);
    #define endl '\n'

    cin >> n >> m >> k;

    for(int i = 1 ; i <= n ; ++i) anc[i] = i;
    for(int i = 1,x,y; i <= k ; ++i) {
        cin >> x >> y;
        merge(x,y);
    }

    for(int i = 1 ; i <= n ; ++i) {
        if(!vis.test(anc[i])) {
            vis.set(anc[i]);
            ++col[sz[anc[i]]];     
        }
    }
    dp.set(0);
    for(int i = 1; i <= n ; ++i)  {
        if(col[i]) {
            compress(i,col[i]);
            for(int j = 1; j <= cnt; ++j) 
                for(int l =n; l >= val[j]; --l)
                    dp.set(l,dp.test(l) || dp.test(l-val[j]));
        }
    }

    int ans = 0;
    for(int i = 1 ; i <= n ; ++i) 
        if(dp[i] && abs(m-i) < abs(m-ans)) {
            ans = i;
        }
    cout << ans <<endl; 

    return 0;
}