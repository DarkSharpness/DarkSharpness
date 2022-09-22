#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5e5 + 32;
#define endl '\n' 
struct node{
    int l,r,x;
    inline bool operator < (const node & T) {
        return r < T.r;
    }
}q[N];

vector <int> vec[N];//存颜色对应的位置
int ans[N];
int s[N];

struct FwTree {
    int sum[N];
    int maxn;
    inline int lowbit(int x) {
        return x&(-x);
    }
    //在loc插入V
    inline void insert(int loc,int V){
        while(loc <= maxn) {
            sum[loc] += V;
            //loc ^= (lowbit(loc)<<1|lowbit(loc));
            loc += lowbit(loc);
        }
    }
    //查询前缀和
    inline int query(int loc) {
        register int ans = 0;
        while(loc) {
            ans += sum[loc];
            loc ^= lowbit(loc);
        }
        return ans;
    }
    inline void initialize(int M) {
        maxn = M;
    }
}t;

int tot = 0;

int main() {
    int n,Q;
    ios::sync_with_stdio(false);
    cin >> n >> Q;
    unordered_map <int,int> mp(n) ;
    mp.reserve(n);
    for(int i = 1; i <= n ; ++i) {
        cin >> s[i];
        int &ref = mp[s[i]];
        if(!ref) ref = ++tot;//开点
        s[i] = ref;//离散化
    }
    for(int i = 0 ; i < Q ; ++i) {
        cin >> q[i].l >> q[i].r;
        q[i].x = i;
    }
    for(int i = 1 ; i <= tot ; ++i) 
        vec[i].push_back(0);//初始化
    sort(q,q+Q);//右端排序
    t.initialize(n);//树状数组初始化
    for(int i = 1,cur = 0 ; i <= n ; ++i) {
        vector <int> & V = vec[s[i]];
        V.push_back(i);
        int len = V.size();
        if(len == 3) {
            t.insert(V[len-3]+1, 1);
            t.insert(V[len-2]+1,-1);
        } else if(len >= 4) {
            t.insert(V[len-4]+1,-1);
            t.insert(V[len-3]+1, 2);
            t.insert(V[len-2]+1,-1);
        }
        while(q[cur].r == i) {
            ans[q[cur].x] = t.query(q[cur].l);
            ++cur;
        }
    }
    for(int i = 0 ; i < Q ; ++i) {
        cout << ans[i] <<endl;
    }
    return 0;
}
