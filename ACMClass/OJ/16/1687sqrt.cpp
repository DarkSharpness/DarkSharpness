#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
pair<int,int> a[N];
int b[N];
ll con[N];//contribution
ll p[N];
int sqrn;
int sqr[N];
int last[N];

void build(int n) {
    sqrn = sqrt(n);
    int k = 1;
    for(int i = 1,j = 1 ; i <= n ; ++i,++j) {
        if(j > sqrn) j = 0,last[k++] = i-1;
        sqr[i] = k;
    }
    last[k] = n ;
}




/**
 * @brief 
 * a[i] ~ a[j] 平方关系以上,直接计算
 * a[i] ~ a[j] 平方关系以内,分块处理,从除以1 ~ sqrta[j] 到乘以1 ~ a[j]
 *  
 */
int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> b[i];
        a[i].second = i;
    }
    sort(a+1,a+n+1);
    for(int i = 1,k = 1; i <=n ; ++i) {//nsqrt(n)
        while(a[k].first * a[k].first <= a[i].first && k != i) ++k;
        --k;
        for(int j = 1; j <= k; ++j) { //a[k].first <
            con[max(a[i].second,a[j].second)] 
              += a[j].first + a[i].first % a[j].first;
        }  
    }
    p[1] = 0;
    int maxn = a[n].first;
    build(maxn);
    for(int i = 2; i <= n; ++i) {
        p[i] = p[i-1] + con[i];
        for(int j = sqrt(b[i]) ; j >= 1 ; ++j) {
            //查询 前缀和 个数
        }
        for(int j = 1 ; j <= b[i] && j * b[i] <= maxn ; ++j) {

        }

    }

    return 0;
}