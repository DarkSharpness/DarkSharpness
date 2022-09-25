#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e5 + 8;
struct node {
    int loc,w,v;
    //����w����
    inline bool operator <(const node &B) const{
        return w < B.w;
    }
}q[N];


//����ģ����
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

//ģ�廯���
void read() {}
template <class T,class ...V>
void read(T& arg,V&... args) {
    Readin(arg);
    read(args...);
}



int tot = 0;
int F[N];//w��һ�γ��ֵ�λ��
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
    //����Ԫ��
    inline void insert(int loc,int val) {
        while(loc <= maxn) {
            ++cnt[loc];
            sum[loc] += val;
            loc += lowbit(loc); 
        }
    }
    //ɾ��Ԫ��
    inline void remove(int loc,int val) {
        while(loc <= maxn) {
            --cnt[loc];
            sum[loc] -= val;
            loc += lowbit(loc); 
        }
    }
    //��ѯǰ׺��
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

//�ܹ� O(nlogn)
inline void update(int& last,const int cur) {
    //Ŀǰֻ��   L[last] ~ n
    //Ŀ���Ǳ�� L[cur]  ~ n
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
//����O(mlogn)
inline ll Get_Y() {
    /*
        Query�������Ϊ 2e5*1e6*2e5
        Ϊ�˷�ֹ���㳬long long
        ���� s*2 ��ֱ�ӽ���
    */
    ll sum = 0;
    for(int i =1 ; i <=m ; ++i)  {
        sum += t.Query(lf[i],rt[i]);
        if(sum > (s<<1)) return sum;//С��֦
    }
    return sum;
}

//ע������±��һ����
inline void discrete() {
    sort(q+1,q+n+1);
    ++n;//�����µĿսڵ�
    q[n].w = q[n-1].w + 1; //���� w
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

//���ֲ���
inline ll Search() {
    ll  ans  = s  ;//�����Ƕ���ѡ,Ȼ������ans
    int last = tot;//last�±���tot���
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

//���� O(mlogn^2+nlogn)
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