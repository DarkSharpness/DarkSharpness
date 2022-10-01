#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 504;
int p[N][N];
int n,m,a,b;

//从fr+1到to行的值
inline int rowsum(int fr,int to) {
    return p[to][m]-p[fr][m];
}
//从l+1,u+1 到 r,d
inline int sum(int l,int r,int u,int d) {
    return p[d][r] - p[d][l] 
         - p[u][r] + p[u][l];
}

inline bool checkrow(int target,int fr,int to) {
    int tot = 0;
    int last = 0;
    for(int i = 1 ; i <= m ; ++i) {
        if(sum(last,i,fr,to) < target) continue;
        ++tot;
        last = i;
        if(tot >= b) return true;
        if(m-i < b-tot) return false;
    }
    return false;
}

inline bool check(int target) {
    int last = 0;
    int tot  = 0;
    for(int i = 1; i <= n ; ++i) { //分割行
        if(rowsum(last,i) < target *b) continue;
        if(!checkrow(target,last,i)) continue;
        ++tot;
        last = i;
        if(tot >= a) return true;
        if(n-i < a-tot) return false;
    }
    return false;
}

inline void read(int &tmp) {
    static char ch;
    while(!isdigit(ch = getchar()));
    tmp = 0;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^ '0');
        ch = getchar();
    }
}


inline void write(int& x) {
    if(!x) putchar('0');
    char ch[12];
    int top = 0;
    while(x) {
        ch[++top] = (x%10) ^ '0';
        x /= 10;
    }
    while(top) {
        putchar(ch[top]);
        --top;
    }
}


int main() {
    read(n);
    read(m);
    read(a);
    read(b);
    for(int i = 1 ; i <= n ; ++i) 
        for(int j = 1 ; j <= m; ++j) {
            read(p[i][j]);
            p[i][j] += p[i][j-1] + p[i-1][j] - p[i-1][j-1];
        }
    if(p[n][m] < a*b) {
        putchar('0');
        return 0;
    }
    int l = 0,
        r = (p[n][m] / (a*b)) + 2;
    int ans = 0;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid)) {
            l = mid+1; 
            ans = mid;
        }
        else {
            r = mid-1;
        }
    }
    write(ans);
    return 0;
}