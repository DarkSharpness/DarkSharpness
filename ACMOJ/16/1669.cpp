#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 504;

int dp[2][N][N];
int loc[N];     //loc[i] = the location of i
int sum[N];     //sum[i] = loc[1] + ... + loc[i]
int c[N][N];
#define endl '\n'

//x ~ y�� x�ľ���
inline int query(int x,int y) {
    return sum[y] - sum[x] - loc[x]*(y-x);
}
//x ~ y�� y�ľ���
inline int rquery(int x,int y) {
    return loc[y] * (y-x) - sum[y-1] + sum[x-1];
}

inline int dist(int x,int y) {
    return loc[y] - loc[x];
}

inline void read(int &tmp) {
    static char ch;
    tmp = 0;
    while(!isdigit(ch = getchar())) ;
    while(isdigit(ch)) {
        tmp = (tmp<<1) + (tmp<<3) + (ch^'0');
        ch = getchar(); 
    }
}

inline void write(int tmp) {
    char ch[10];    
    int tot = -1;
    while(tmp) {
        ch[++tot] = (tmp%10) ^ '0';
        tmp /= 10;
    }
    while(tot != -1) {
        putchar(ch[tot]);
        --tot;
    }
}



int main() {
    int n,m;
    read(n);
    read(m);
    loc[1] = 0;
    sum[1] = 0;
    for(int i = 2; i <= n ; ++i) {
        read(loc[i]);
        loc[i] += loc[i-1];
        sum[i] =  sum[i-1] + loc[i];
    }

    for(int i = 1; i <= n ; ++i) {
        int k = i+1;
        for(int j = i + 1; j <= n; ++j) {
            while((loc[k]<<1) <= loc[i]+loc[j]) ++k;
            c[i][j] -= query(i,j); 
            c[i][j] += query(i,k-1)+rquery(k,j);
        }
    }

    memset(dp,30,sizeof(dp));

    for(int j = 1 ; j <= n ; ++j) {
        for(int k = 1  ;  k < j ; ++k) 
            dp[1][j][k] = dp[1][j-1][k] + dist(k,j);
        dp[1][j][j] = rquery(1,j);
    }
    for(int t = 2,i = 1; t <= m ; ++t) {
        i ^= 1;// i = t & 1
        for(int j = t ; j <= n ; ++j) {
            for(int k = t  ;  k < j ; ++k) 
                dp[i][j][k] = dp[i][j-1][k] + dist(k,j);
            dp[i][j][j] = 114514 << 11; //��ʼ����dp[i][j][j]
            for(int g = t-1 ; g < j ; ++g) {//ȡmin
                dp[i][j][j] = min(dp[ i ][j][j],
                        c[g][j] + dp[i^1][j][g]);
            }
        }
    }

    int ans = 1919810 << 10;
    for(int i = m ; i <= n ; ++i){
        ans = min(ans,dp[m & 1][n][i]);
    }
    write(ans);
    return 0;
}