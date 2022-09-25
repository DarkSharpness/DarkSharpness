#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//const int N = 10;
//const int M = 20;
const int M = 1919810 ;
const int N = 114514<<2;

struct Queue{
    int data[M<<1];
    int head,tail;
    inline void push(int x) {
        data[tail++] = x;
    }
    inline void pop() {
        ++head;   
    }
    inline int front() {
        return data[head];
    }
    inline bool empty() {
        return head == tail;
    }
    Queue() {
        head = tail = 0;
    }
};

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
Queue q;

/// @brief Shortest Path Slow Algorithm
inline void SPSA(const int start,const int terminal) {
    dp[start] = 0;
    if(t[start] < 0) return; //防止一开始就走不动
    q.push(start);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for(int i = head[u] ; i ; i = e[i].nxt) {
            int  v  = e[i].to;
            ll  sum = dp[u] + e[i].len;
            if((sum <= t[v]) && sum < dp[v] ) {
                dp[v] = sum;
                if(!vis[v] && v!= terminal) {
                    q.push(v);
                    vis[v] = true;
                }
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
        read(x);read(y);read(g);
        adde(x,y,g);
        adde(y,x,g);
    }

    SPSA(S,T);

    //slow output
    if(dp[T] == dp[0]) puts("sad");
    else printf("%lld\n",dp[T]);
    return 0;
}