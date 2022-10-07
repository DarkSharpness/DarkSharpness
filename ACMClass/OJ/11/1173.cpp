#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

inline void read(int &tmp) {
    static char ch;
    while(!isdigit(ch = getchar()));
    tmp = 0;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^ '0');
        ch = getchar();
    }
}
int n;
const int N = 1e5 + 9;
int a[N];
int b[N];
int A[N];
int B[N];
int maxa,maxb;
int topa,topb;

inline void WORK_1() {
    sort(A+1,A+1+n);
    sort(B+1,B+1+n);
}

inline void WORK_2() {
    for(int i = 1; i <= maxa; ++i)
        while(a[i]--) {
            A[++topa] = i;
        }
    for(int i = 1; i <= maxb; ++i)
        while(b[i]--) {
            B[++topb] = i;
        }
}


int main() {
    read(n);
    for(int i = 1,x; i <=n ; ++i) {
        read(x);
        ++a[x];
        A[i] = x;
        if(x > maxa) maxa = x;
    }
    for(int i = 1,x; i <=n ; ++i) {
        read(x);
        ++b[x];
        B[i] = x;
        if(x > maxb) maxb = x;
    }
    if(max(maxa,maxb) >= n*13) 
        WORK_1();
    else WORK_2();
    long long ans1 = 0,
              ans2 = 0;
    for(int i = 1 ; i <= n ; ++i) {
        ans1 += (long long)(A[i]) * B[i];
        ans2 += (long long)(A[i]) * B[n-i+1];
    }
    printf("%lld %lld",ans1,ans2);

    return 0;
}
