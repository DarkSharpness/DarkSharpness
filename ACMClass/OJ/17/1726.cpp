#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long
const int N = 1008;
int a[N << 1];
int n;
queue <pair<int,int>> q;
inline int dis(int x,int y) {
    return y >= x ? (y-x)*(y-x) :
                 (y-x+n)*(y-x+n);                   
}

int work(int loc) {
    int ret = 0;
    if(a[loc] > 1)
        q.emplace(loc,a[loc]-1);
    for(int i = loc+1 ; i != loc ; ++i) {
        if(i >= n) i -= n;
        if(a[i]) q.emplace(i,a[i]);
        if(q.empty()) return 1919810;
        int & tmp = q.front().second;
        --tmp;
        ret += dis(q.front().first,i);
        if(!tmp) q.pop();
    }
    return ret;
}

signed main() {
    scanf("%d",&n);
    for(int i = 0 ; i < n ; ++i) scanf("%d",a+i);
    int ans = 1919810;
    for(int i = 0 ; i < n ; ++i) 
        if(a[i]) ans = min(ans,work(i)); 
    printf("%d",ans);
    return 0;
}