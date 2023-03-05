#include <bits/stdc++.h>
// #include <Dark/inout>
// #define int long long
// using ll = long long;
// using ull = unsigned long long;
using namespace std;


double t[100];
double x[100];
double v[100];
double a[100];


signed main() {
    freopen("test.txt","r",stdin);
    for(int i = 0 ; i < 15 ; ++i) scanf("%lf",t + i);
    for(int i = 0 ; i < 15 ; ++i) scanf("%lf",x + i);
    freopen("v.out","w",stdout);
    for(int i = 0 ; i < 14 ; ++i)
        v[i] =  (x[i + 1] - x[i]) / (t[i + 1] - t[i]);
    for(int i = 0 ; i < 13 ; ++i)
        a[i] =  (v[i + 1] - v[i]) / (t[i + 1] - t[i]);
    for(int i = 0 ; i < 14 ; ++i) {
        printf("%.2lf\t%.2lf\n",t[i],v[i]);
    }
    puts("");
    for(int i = 0 ; i < 13 ; ++i) {
        printf("%.2lf\t%.2lf\n",t[i],a[i]);
    }
    return 0;
}