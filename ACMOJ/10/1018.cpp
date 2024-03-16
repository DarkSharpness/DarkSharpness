#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
//#define int long long

const int N = 1025;
const int M = 3432; //14C7
const int S = 1<<16;//state number
const int P = 5150;//7!
int m = 0,n,k;


int bucket[N * N];

inline long long match(int *a1,int size1,int *a2,int size2,int target){
    long long cnt = 0;
    for(int i = 0 ; i < size1 ; ++i)
        ++bucket[a1[i]];
    for(int i = 0 ; i < size2 ; ++i) 
        if(target >= a2[i] && bucket[target-a2[i]]) 
            cnt += bucket[target-a2[i]];
    for(int i = 0 ; i < size1 ; ++i) 
        bucket[a1[i]] = 0;
    return cnt;
}

//Find reverse number of a sequence
inline int getrev(const vector<int> &tmp) {
    int ans = 0;
    for(int i = 0 ; i < tmp.size() ;++i) 
        for(int j = 0 ; j < i ; ++j)
            if(tmp[j] > tmp[i]) ++ans;
    return ans;
}

int cnt[S];  //number of i
int rev[S];  //inverted sequence of i
int w[N][N]; //w[i][j] count x < i,a[x] > j
int v[N][N]; //v[i][j] count x : i,a[x] < j
vector <int> perm1(P);//1
int rev1[P];
vector <int> perm2(P);//2
int rev2[P];
int loc[16]; //location of ith unused
int num[16]; //number of unused from small to big
int a[N],cur;
bool vis[N];
int l,r;

bool vis1[10];
bool vis2[10];



inline void dfs1() {
    vector <int> tmp;
    for(int i = 0 ; i < l ; ++i)
        tmp.push_back(i);
    do{
        int code = 0;
        for(int i = 0 ; i < l ; ++i) 
            code = code * l + tmp[i];
        rev1[perm1.size()] = getrev(tmp);
        perm1.push_back(code);
    }while(next_permutation(tmp.begin(),tmp.end()));
}

void dfs2() {
    vector <int> tmp;
    for(int i = 0 ; i < r ; ++i)
        tmp.push_back(i);
    do{
        int code = 0;
        for(int i = 0 ; i < r ; ++i) 
            code = code * r + tmp[i];
        rev2[perm2.size()] = getrev(tmp);
        perm2.push_back(code);
    }while(next_permutation(tmp.begin(),tmp.end()));
}

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
        if(!vis[i]) num[sum++] = i;
    sort(num,num+sum);
    perm1.resize(0);
    perm2.resize(0);
    dfs1();
    dfs2();
}


//Sum = cur + each + between + inner
//state :  1 - first m>>1  //   0 - last (m+1)>>1
int tmp1[P],
    tmp2[P];
inline long long work(int state) {
    int sum = cur + rev[state];
    if(sum > k) return 0;
    sum = k - sum ;//剩余量
    vector <int> num1,num2;
    for(int i = 0 ; i < m ;++i) {
        if(state & (1 << i)) num1.push_back(num[i]);
        else                 num2.push_back(num[i]);
    }
    for(int i = 0; i < perm1.size() ; ++i) {
        int ret = 0 ;
        int code = perm1[i];
        for(int j = l-1 ; j >= 0 ; --j) {
            int locnow = loc[code % l];//当前位置
            ret += w[locnow][num1[j]]+v[locnow][num1[j]];
            code /= l;
        }
        tmp1[i] = rev1[i] + ret;
    }
    for(int i = 0; i < perm2.size() ; ++i) {
        int ret = 0 ;
        int code = perm2[i];
        for(int j = r-1 ; j >= 0 ; --j) {
            int locnow = loc[code % r + l];//当前位置
            ret += w[locnow][num2[j]]+v[locnow][num2[j]];
            code /= r;
        }
        tmp2[i] = rev2[i] + ret;
    }
    return match(tmp1,perm1.size(),tmp2,perm2.size(),sum);
}



inline void count() {
    cnt[0] = 0 ;
    //cout << cur << endl;
    rev[0] = 0 ;
    long long aans = 0;
    for(int i = 0 ; i < 1<<m ; ++i) {
        cnt[i<<1]   = cnt[i];
        cnt[i<<1|1] = cnt[i] + 1;
        rev[i<<1]   = rev[i] + cnt[i<<1];
        rev[i<<1|1] = rev[i];
        if(cnt[i] == l) aans += work(i);
    }
    printf("%lld\n",aans);
}



signed main() {
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