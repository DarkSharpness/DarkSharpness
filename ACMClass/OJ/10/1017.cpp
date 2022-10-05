#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[114514];
int count1(int i) {
    int ret = 0;
    while(i) {
        if(i & 1) ++ ret;
        i >>= 1; 
    }
    return ret;
}


int main() {
    a[1] = 1;
    for(int i = 1 ; i <= 100 ; ++i) {
        a[i<<1]     = a[i];
        a[(i<<1)-1] = a[i] + a[i-1];
        cout << (i) << ':' << a[i] << endl;
    } 
    return 0;
}