#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e5 + 8;
struct node {
    int loc,w,v;
    //按照w排序
    inline bool operator <(const node &B) const{
        return w < B.w;
    }
}q[N];


//单个模板快读
template <class T>
inline void Readin(T &tmp) {
    tmp = 0;
    static char ch;
    while(!isdigit(ch = getchar()));
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^ '0');
        ch = getchar();
    }
}

//模板化快读
void read() {}
template <class T,class ...V>
void read(T& arg,V&... args) {
    Readin(arg);
    read(args...);
}



int tot = 0;
int F[N];//w第一次出现的位置
struct FwTree {
    private:

    struct Fnode{
        int cnt;
        ll  sum;
        ll operator*(const Fnode &B) {
            cnt -= B.cnt;
            sum -= B.sum;
            return cnt*sum;
        }
        Fnode(int Cnt,ll Sum) {
            cnt = Cnt;
            sum = Sum;
        }
    };

    int cnt[N];
    ll sum[N];    
    int maxn;
    inline int lowbit(int x) {
        return x&(-x);
    }
    //插入元素
    inline void insert(int loc,int val) {
        while(loc <= maxn) {
            ++cnt[loc];
            sum[loc] += val;
            loc += lowbit(loc); 
        }
    }
    //删除元素
    inline void remove(int loc,int val) {
        while(loc <= maxn) {
            --cnt[loc];
            sum[loc] -= val;
            loc += lowbit(loc); 
        }
    }
    //查询前缀和
    inline Fnode query(int loc) {
        int counter = 0;
        ll  pre_val = 0;
        while(loc) {
            counter += cnt[loc];
            pre_val += sum[loc];
            loc  ^= lowbit(loc);
        }
        return Fnode(counter,pre_val);
    }
    public :
    inline void Insert(int loc,int val) {
        insert(loc,val);
    }
    inline void Remove(int loc,int val) {
        remove(loc,val);
    }
    inline ll Query(int L,int R) {
        return query(R) * query(L-1);
    }
    inline void init(int n) {
        maxn = n;
    } 
}t;

//last >= 1
//cur  >= 1;

//总共 O(nlogn)
inline void update(int& last,const int cur) {
    //目前只有   L[last] ~ n
    //目标是变成 L[cur]  ~ n
    if(last < cur) {
        for(int i = F[last] ; i <= F[cur]-1 ; ++i) 
            t.Remove(q[i].loc,q[i].v);
    } else {
        for(int i = F[cur] ; i <= F[last]-1 ; ++i) 
            t.Insert(q[i].loc,q[i].v);
    }
    last = cur;
}
 
int lf[N],rt[N];
int n,m;
ll s;
//单次O(mlogn)
inline ll Get_Y() {
    /*
        Query单次最大为 2e5*1e6*2e5
        为了防止计算超long long
        超过 s*2 后直接结束
    */
    ll sum = 0;
    for(int i =1 ; i <=m ; ++i)  {
        sum += t.Query(lf[i],rt[i]);
        if(sum > (s<<1)) return sum;//小减枝
    }
    return sum;
}

//注意二分下标的一致性
inline void discrete() {
    sort(q+1,q+n+1);
    ++n;//插入新的空节点
    q[n].w = q[n-1].w + 1; //最大的 w
    q[n].v = 0;
    q[n].loc = n;
    t.init(n);
    tot = 0 ;
    for(int i = 1,pre = -1; i <=n ; ++i) {
        if(q[i].w != pre) {
            F[++tot] = i;
            pre = q[i].w;
        }
        q[i].w = tot;
    }
}

//二分查找
inline ll Search() {
    ll  ans  = s  ;//最差就是都不选,然后变成了ans
    int last = tot;//last下标是tot相关
    int l =  1 ,   
        r = tot,
        mid;
    while(1) { 
        mid = (l+r) >> 1;
        update(last,mid);
        ll Y = Get_Y();
        ans = min(ans,abs(Y-s));
        if(l == r || !ans) return ans;
        if(Y > s) l = mid +1;
        else      r = mid;
    }
    
}

//理论 O(mlogn^2+nlogn)
int main() {
    read(n,m,s);
    for(int i = 1; i <= n ; ++i) {
        read(q[i].w,q[i].v);
        q[i].loc = i;
    }
    for(int i = 1; i <= m ; ++i) read(lf[i],rt[i]);
    discrete();
    printf("%lld\n",Search());
    return 0;
}