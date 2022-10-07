#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1024;
const int M = 3432; //14C7
const int S = 1<<16;//×´Ì¬Êı
int m = 0,n,k;


int cnt[S];  //number of i
int rev[S];  //inverted sequence of i
int w[N][N]; //w[i][j] count x before i,a[x] > j
int v[N][N]; //v[i][j] count x after  i,a[x] < j
int perm1[674801];//7^8ÅÅĞò
vector <int[8]> permL;
int perm2[674801];
vector <int[8]> permR;
int loc[16];
int num[16];
int a[N],cur;
bool vis[N];
int l,r;

inline void prework() {
    for(int i = 1 ; i <= n ; ++i) {
        for(int j = 1 ; j <= n ; ++j)
            w[i][j] = w[i-1][j];
        if(!a[i]) continue;
        for(int j = 1 ; j < a[i] ; ++j)
            ++w[i][j];
    }
    for(int i = n ; i >= 1 ; --i) {
        for(int j = 1 ; j <= n ; ++j)
            v[i][j] = v[i+1][j];
        if(!a[i]) continue;
        for(int j = n ; j > a[i] ; --j)
            ++v[i][j];
    }
    for(int i = 1 ; i <= n ; ++i) 
        cur += w[i][a[i]];
    int sum = 0;
    for(int i = 1 ; i <= n ; ++i) 
        sum += v[i][a[i]];
    //printf("%d %d\n",cur,sum);
    sum = 0;
    for(int i = 1 ; i <= n ; ++i) 
        if(!vis[i]) num[sum++] = i;
    sort(num,num+sum);
    for(int i = pow(l,l)-1 ; i >= 1 ; --i) {
        
    }
}



//Sum = cur + each + between + inner
//state :  1 - first m>>1  //   0 - last (m+1)>>1
inline int work(int state) {
    int sum = cur + rev[state];
    if(sum > k) return 0;
    for(int i : permL) {
        
    }
    return 0;
}



inline void count() {
    cnt[0] = 0 ;
    rev[0] = 0 ;
    int ans = 0;
    for(int i = 0 ; i < 1<<m ; ++i) {
        cnt[i<<1]   = cnt[i];
        cnt[i<<1|1] = cnt[i] + 1;
        rev[i<<1]   = rev[i] + cnt[i<<1];
        rev[i<<1|1] = rev[i];
        //printf("%d %d %d\n",i,cnt[i],rev[i]);
        if(cnt[i] == l) ans += work(i);
    }
    printf("%d\n",ans);
}



int main() {
    scanf("%d%d",&n,&k);
    for(int i = 1 ; i <= n ; ++i) {
        scanf("%d",a+i);
        if(!a[i]) loc[m++] = i;
        else vis[a[i]] = true;
    }
    l = m >> 1;
    r = m - l;
    if(k > (n*(n-1))>>1) {
        puts("0");
        return 0;
    }
    prework();
    if(cur > k) {
        puts("0");
        return 0;
    }
    count();
    return 0;
}