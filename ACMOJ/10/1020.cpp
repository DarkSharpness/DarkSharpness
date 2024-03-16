#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M = 5e5 + 2;
const int N = 1e5 + 2;
struct edge{
    int to;
    int len;
    int nxt;
}e[M<<1],E[M<<1],f[M<<1];
int tot = 0,head[N],TOT = 0,HEAD[N];
inline void adde(int fr,int to,int len){
    e[++tot].to = to;
    e[tot].nxt  = head[fr];
    e[tot].len  = len;
    head[fr]    = tot;
}
inline void addE(int fr,int to,int len){
    E[++TOT].to = to;
    E[TOT].nxt  = HEAD[fr];
    E[TOT].len  = len;
    HEAD[fr]    = TOT;
}

long long dist[N];
long long d[N][11];

bitset <N> vis,vis2,used[11];

void dijkstra(int end) {
    memset(dist,62,sizeof(dist));
    priority_queue< pair<long long,int> > q;
    dist[1] = 0; 
    q.emplace(0,1);
    while(!q.empty()) {
        int x = q.top().second;
        q.pop();
        if(vis.test(x)) continue;
        vis.set(x);
        long long sum;
        for(int i = head[x] ; i ; i = e[i].nxt) {
            int y = e[i].to;
            sum = dist[x] + e[i].len;
            if(sum < dist[y]) {
                dist[y] = sum;
                HEAD[y] = 0;//清空之前的边
                addE(y,x,0);
                if(e[i].to != end)
                    q.emplace(-sum,e[i].to);
            } else if(sum == dist[e[i].to]) {
                addE(y,x,0);
            }
        }
    }
}

void dfs(int id) {
    for(int i = HEAD[id] ; i ; i = E[i].nxt) {
        if(!vis2[E[i].to]) {
            vis2[E[i].to] = 1;
            dfs(E[i].to);
        }
    }
}
inline bool judge(int x,int y) {
    if(dist[y] > dist[x] && vis2[x] && vis2[y]) return true;
    return false;
}


void bfs(int end,int k) {
    memset(d,62,sizeof(d));
    //-距离 层数 编号
    priority_queue< pair<pair<long long,int>,int> > q;
    #define mp make_pair
    q.push(mp(mp(0,0),1));
    d[1][0] = 0;
    while(!q.empty()) {
        int x = q.top().second;      //当前编号
        int z = q.top().first.second;//当前层数
        q.pop();
        if(used[z].test(x)) continue;
        used[z].set(x);
        long long sum;
        for(int i = head[x] ; i ; i = e[i].nxt) {
            int y = e[i].to;             //目标编号
            int t = judge(x,y) ? z+1 : 0;//目标层数
            if(t >= k) continue;          //超过了就不走
            sum = d[x][z] + e[i].len;    //
            if(sum < d[y][t]) {
                //cout << x <<" "<< y << " "<< t << endl;
                d[y][t] = sum;
                //cout << y << " " << t <<endl;
                if(y != end) q.push(mp(mp(-sum,t),y));
            }
        }
    }
    long long ans = d[0][0];
    for(int i = 0 ; i < k ; ++i) ans = min(ans,d[end][i]);
    cout << ((ans == d[0][0])? -1 : ans ) << endl; 
}

inline int read() {
    static int  tmp ;
    static char ch  ;
    tmp  = 0;  
    ch   = getchar();
    while(ch < '0' || ch > '9') {
        ch = getchar();
    }
    while(ch >= '0'&&ch <= '9') {
        tmp = tmp * 10 + (ch ^ '0');
        ch  = getchar();
    }
    return tmp;
}
char ch[20];


void write(long long x) {
    if(!x) {putchar('0'),putchar('\n');return;}
    int cnt = -1;
    while(x) {
        ch[++cnt] = (x % 10) ^ '0';
        x /= 10;
    }
    while(cnt != -1) {
        putchar(ch[cnt]);
        --cnt;
    }
    putchar('\n');
}


int main() {
    //ios::sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    for(int i = 1,x,y,z,w ; i <= m ; ++i) {
        //cin >> x >> y >> z >> w;
        x = read();
        y = read();
        z = read();
        w = read();
        adde(x,y,z);
        if(w == 1) adde(y,x,z);
    }
    dijkstra(n);
    vis2[n] = 1;
    dfs(n);
    bfs(n,k);
    return 0;
}