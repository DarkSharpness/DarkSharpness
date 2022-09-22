#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e4 + 32;
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
int cnt = 0;
int val[N]; //价值val = 体积unit

inline void compress(int unit,int SZ){
    int i = 1;
	cnt = 0;
	while(SZ > i)
	{
		SZ -= i;
		val[++cnt] = i*unit;
		i <<= 1;
	}
	val[++cnt]= SZ*unit;
}

bitset <N> dp;

int main() {
    int n,m,k;
    ios::sync_with_stdio(false);
    #define endl '\n'
    cin >> n >> m >> k;
    //double ti = clock();
    for(int i = 1 ; i <= n ; ++i) anc[i] = i;
    for(int i = 1,x,y; i <= k ; ++i) {
        cin >> x >> y;
        merge(x,y);
    }

    //vector <int> col;
    //col.reserve(n);
    for(int i = 1 ; i <= n ; ++i) 
        if(anc[i] == i) {
            ++col[sz[i]];
        }     
    dp.set(0);
    for(int i = 1 ; i <= n ; ++i)  {
        if(col[i] != 0) { 
            compress(i,col[i]);
            for(int j = 1; j <= cnt; ++j) 
                dp |= dp << val[j];
        }
    }

    int ans = 0;
    for(int i = 1 ; i <= n ; ++i) 
        if(dp[i] && abs(m-i) < abs(m-ans)) 
            ans = i;
    cout << ans <<endl; 
    return 0;
}