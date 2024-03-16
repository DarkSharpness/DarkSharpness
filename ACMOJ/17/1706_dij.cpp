#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//const int N = 10;
//const int M = 20;
const int M = 1919810 ;
const int N = 114514<<2;


struct edge{
    int nxt,to,len;
}e[M<<1];
int head[N],tot;
inline void adde(int fr,int to,int len) {
    e[++tot].to = to;
    e[tot].nxt  = head[fr];
    e[tot].len  = len;
    head[fr]    = tot;
}
ll t[N];
ll dp[N];
bitset <N> vis; //表示在不在队列里面
priority_queue <pair<long long,int>> q;

inline void dijkstra(const int start,const int terminal) {
    if(t[start] < 0) return; //防止一开始就走不动
    dp[start] = 0;
    q.emplace(0,start);
    while(!q.empty()) {
        int u = q.top().second;
        q.pop();
        if(vis[u]) continue; 
        vis[u] = true;
        for(int i = head[u] ; i ; i = e[i].nxt) {
            int  v  = e[i].to;
            ll  sum = dp[u] + e[i].len;
            if((sum <= t[v] || v== terminal) && sum < dp[v] ) {
                dp[v] = sum;
                if(v!= terminal) 
                    q.emplace(-sum,v);
            }
        }
    }

}
/// @brief Slow Read-in 
inline void read(int &tmp) {
    tmp = 0;
    static char ch;
    while(!isdigit(ch = getchar()));
    while(isdigit(ch)) {
        tmp = tmp*10 + ('0'^ch);
        ch = getchar();
    }
}


int main() {
    memset(dp,30,sizeof(dp));
    int n,m,S,T,g,q;
    read(n);read(m);read(S);
    read(T);read(g);read(q);
    int x,y;
    if(q != 0) {
        for(int i = 1 ; i <=n ; ++i) {
            read(x);read(y);
            if(y>=x) 
                 t[i] = min((y-x)/q , g);//最晚时间
            else t[i] = -1;
        }
    } else {
        for(int i = 1 ; i <=n ; ++i) {
            read(x);read(y);
            if(y>=x) t[i] =  g;
            else     t[i] = -1;//到不了             
        }
    }
    
    while(m--) {
        int f;
        read(x);read(y);read(f);
        adde(x,y,f);
        adde(y,x,f);
    }

    dijkstra(S,T);

    //slow output
    if(dp[T] == dp[0] || dp[T] > g) puts("sad");
    else printf("%lld\n",dp[T]);
    return 0;
}