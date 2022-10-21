#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long


int n,m;
int cnt[5];
int a[400];
constexpr int N = 3e6;
int sum[N];
int pre[5];
int val[N];


signed main() {
    scanf("%d%d",&n,&m);
    for(int i = 0 ; i < n ; ++i) scanf("%d",a+i);
    for(int i = 1,x; i <= m ; ++i) 
        scanf("%d",&x),++cnt[x];
    pre[4] = 1;
    for(int i = 3 ; i >= 1 ; --i) pre[i] = pre[i+1] * (cnt[i+1]+1);
    int index = -pre[1]-pre[2]-pre[3]-pre[4];
    for(int i = 0 ; i <= cnt[1] ; ++i) {
        for(int j = 0; j <= cnt[2] ; ++j) {
            for(int k = 0 ; k <= cnt[3] ; ++k) {
                for(int l = 0; l <= cnt[4] ; ++l) {
                    index = pre[1] * i +
                            pre[2] * j +
                            pre[3] * k +
                            pre[4] * l;
                    val[index] = sum[index]
                                 + a[i * 1 +
                                     j * 2 +
                                     k * 3 +
                                     l * 4] ;
                    if(i != cnt[1]) {
                        if(val[index] > 
                           sum[index+pre[1]])
                            sum[index+pre[1]] = val[index]; 
                    }
                    if(j != cnt[2]) {
                        if(val[index] > 
                           sum[index+pre[2]])
                            sum[index+pre[2]] = val[index]; 
                    }
                    if(k != cnt[3]) {
                        if(val[index] > 
                           sum[index+pre[3]])
                            sum[index+pre[3]] = val[index]; 
                    }
                    if(l != cnt[4]) {
                        if(val[index] > 
                           sum[index+pre[4]])
                            sum[index+pre[4]] = val[index]; 
                    }
                }
            }
        }
    }
    printf("%d",val[index]);

    return 0;
}