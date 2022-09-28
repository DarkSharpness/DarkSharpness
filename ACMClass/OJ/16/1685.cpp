#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5e5 + 32;
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

inline void read(int &tmp) {
    static char ch;
    tmp = 0;
    while(!isdigit(ch = getchar())) ;
    while(isdigit(ch)) {
        tmp = (tmp<<1) + (tmp<<3) + (ch^'0');
        ch = getchar(); 
    }
}

char ch[10];    
int ttt = -1;  
inline void write(int& tmp) {
    if(!tmp) {
        puts("0");
        return ;
    }
    while(tmp) {
        ch[++ttt] = (tmp%10) ^ '0';
        tmp /= 10;
    }
    while(ttt != -1) {
        putchar(ch[ttt]);
        --ttt;
    }
    putchar('\n');
}
int main() {
    int n,Q;
    read(n);
    read(Q);
    unordered_map <int,int> mp ;
    mp.reserve(n<<1);
    for(int i = 1; i <= n ; ++i) {
        read(s[i]);
        int &ref = mp[s[i]];
        if(!ref) ref = ++tot;//开点
        s[i] = ref;//离散化
    }
    for(int i = 0 ; i < Q ; ++i) {
        read(q[i].l);
        read(q[i].r);
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
        write(ans[i]);
    }
    return 0;
}
