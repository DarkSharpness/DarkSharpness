#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 8;
int A[N];
/// @brief Fast read-in
inline void read(int &tmp) {
    tmp = 0;
    register bool fl = false;
    register char ch = getchar();
    while(!isdigit(ch)) {
        if(ch == '-') fl = true;
        ch = getchar();
    }
    while(isdigit(ch)) {
        tmp = (tmp<<1) + (tmp<<3) +(ch^'0');
        ch = getchar();
    }
    if(fl) tmp = -tmp;
}


int main() {
    int n,x;
    read(n);
    for(int i = 1; i <= n ; ++i) read(A[i]);
    for(int i = 1; i <= n ; ++i) {
        read(x);
        A[i] -= x;
    }
    //²î·Ö
    for(int i = n;  i ; --i) A[i]-=A[i-1];
    //for(int i = 1; i<=n ; ++i) cout << A[i] <<endl;
    unsigned long long cnt1=0,cnt2=0;
    for(int i =1 ; i <=n ; ++i) {
        if(A[i] > 0) cnt1 += A[i];
        else cnt2 -= A[i]; 
    }
    printf("%llu\n",max(cnt1,cnt2));
    return 0;
}