#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1024;
const int M = 3432; //14C7
const int S = 1<<16;//state number
const int P = 5150;//7!
int m = 0,n,k;


inline int match(int *a1,int size1,int *a2,int size2,int target){
    sort(a1,a1+size1);
    sort(a1,a2+size2);
    int i = 0,
        j = size2-1;
    int cnt = 0,
        cnt1= 0,
        cnt2= 0;
    while(i != size1 && j != -1) {
        while(i != size1-1 && a1[i] == a1[i+1]) {++cnt1,++i;}
        while(j != 0       && a2[j] == a2[j-1]) {++cnt2,--j;}
        if(a1[i] + a2[j] == target)     {cnt+=cnt1*cnt2,++i;cnt1=1;}
        else if(a1[i] + a2[j] > target) {--j,cnt2=1;}
        else                            {++i,cnt1=1;} 
    }  
    return cnt;
}

int cnt[S];  //number of i
int rev[S];  //inverted sequence of i
int w[N][N]; //w[i][j] count x before i,a[x] > j
int v[N][N]; //v[i][j] count x after  i,a[x] < j
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

//求出逆序对
inline int getrev(int num,int base) {
    static int a[10];
    int ans = 0;
    for(int i = 0 ; i < base ; ++i) {
        a[base-i+1] = num % base;
        num /= base;
    }
    for(int i = 0 ; i < base ; ++i)
        for(int j = 0 ; j < base ; ++j) 
            if(a[j] > a[i]) ++ ans;
    return ans;
}

void dfs1(int cur,int num) {
    if(cur == l) {
        rev1[perm1.size()] = getrev(num,l);
        perm1.push_back(num);
    }
    for(int i = 0; i < l ; ++i) {
        if(!vis1[i]) {
            vis1[i] = true;
            dfs1(cur+1,num*l+i);
            vis1[i] = false;
        }
    }
}

void dfs2(int cur,int num) {
    if(cur == r) {
        rev2[perm2.size()] = getrev(num,r);
        perm2.push_back(num);
    }
    for(int i = 0; i < r ; ++i) {
        if(!vis2[i]) {
            vis2[i] = true;
            dfs2(cur+1,num*l+i);
            vis2[i] = false;
        }
    }
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
    //for(int i = 1 ; i <= n ; ++i) 
        //sum += v[i][a[i]];
    //printf("%d %d\n",cur,sum);
    //sum = 0;
    for(int i = 1 ; i <= n ; ++i) 
        if(!vis[i]) num[sum++] = i;
    sort(num,num+sum);
    perm1.resize(0);
    perm2.resize(0);
    dfs1(0,0);
    dfs2(0,0);
}


//Sum = cur + each + between + inner
//state :  1 - first m>>1  //   0 - last (m+1)>>1
int tmp1[P],
    tmp2[P];
inline int work(int state) {
    int sum = cur + rev[state];
    if(sum > k) return 0;
    sum = k - sum ;//剩余量
    vector <int> num1,num2;
    for(int i = 0 ; i < m ;++i) {
        if(state & (1 << i)) num1.push_back(num[i]);
        else num2.push_back(num2[i]);
    }
    for(int i = 0; i < perm1.size() ; ++i) {
        int ret = 0 ;
        int tmp = perm1[i];
        for(int j = l-1 ; j >= 0 ; --j) {
            int locnow = loc[tmp % l];//当前位置
            ret += w[locnow][num[j]]+v[locnow][num[j]];
            tmp /= l;
        }
        tmp1[i] = rev1[i] + ret;
    }
    for(int i = 0; i < perm2.size() ; ++i) {
        int ret = 0 ;
        int tmp = perm2[i];
        for(int j = r-1 ; j >= 0 ; --j) {
            int locnow = loc[tmp % r + l];//当前位置
            ret += w[locnow][num[j]]+v[locnow][num[j]];
            tmp /= r;
        }
        tmp2[i] = rev2[i] + ret;
    }
    return match(tmp1,perm1.size(),tmp2,perm2.size(),sum);
}



inline void count() {
    cnt[0] = 0 ;
    rev[0] = 0 ;
    int ans = 0;
    for(int i = 0 ; i < 1<<m ; ++i) {
        cnt[i<<1]   = cnt[i];
        cnt[i<<1|1] = cnt[i] + 1;
        rev[i<<1]   = rev[i] + cnt[i<<1];
        rev[i<<1|1] = rev[i];
        //printf("%d %d %d\n",i,cnt[i],rev[i]);
        if(cnt[i] == l) ans += work(i);
    }
    printf("%d\n",ans);
}



int main() {
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