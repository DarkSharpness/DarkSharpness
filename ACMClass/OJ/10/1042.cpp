#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 504;
int a[N][N];
struct edge{
    int nxt,to;
}e[N*N<<1];
int head[N],tot;
inline void adde(int fr,int to) {
    e[++tot].to = to;
    e[tot].nxt  = head[fr];
    head[fr]    = tot;
}



int main() {

    return 0;
}