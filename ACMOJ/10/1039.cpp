#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M = 262152;
const int N = 100009;

inline void read(int &tmp) {
    static char ch;
    while(!isdigit(ch = getchar()));
    tmp = 0;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^ '0'); 
        ch = getchar();
    }
}


int a[N];
int s[N];
int tag[M];
bitset <M> vis;
int n;

// O(1)
inline int getdim(int val,int dim) {
    return (val/s[dim])%a[dim]; 
}

//°´ÕÕÑÕÉ«dfs
int col;
int idx;
void dfs() {
    if(vis[idx] || tag[idx] != col) return;
    vis[idx] = true;
    for(int i = 1; i <= n ; ++i) {
        int dim = getdim(idx,i);
        if(dim-1 >= 0) {
            idx -= s[i];
            dfs();
            idx += s[i];
        } 
        if(dim+1 < a[i]) {
            idx += s[i];
            dfs();
            idx -= s[i];
        }
    }
}


int main() {
    int m;
    read(m);
    for(int i = 1 ; i <= m ; ++i) {
        read(*a);
        if(*a > 1) a[++n] = *a;
    }
    s[n] = 1;
    for(int i = n ; i >= 1 ; --i) 
        s[i-1] = s[i] * a[i];
    for(int i = 0 ; i < *s/*s[0]*/ ; ++i) 
        read(tag[i]);
    //cout << s[0] <<  '\n';
    int ans = 0;
    for(int i = 0 ; i < *s ; ++i) {
        if(!vis[i]) {
            ++ans;
            col = tag[i];
            idx = i;
            dfs();
        }
    }
    printf("%d",ans);
    return 0;
}