#include<bits/stdc++.h>
#include<General/inout.h>
using namespace std;
typedef long long ll;

int a[10] = {   
5,4,3,2,1
};
int top = 4;
ll f(ll x) {
    ll ans = a[0];
    ll base = x;
    Loop(i,1,top) {
        ans += a[i] * base;
        base *= x;
    }
    return ans;
}

ll C(ll n,int m) {
    ll ans = 1;
    for(int i = m+1 ; i <= n ; ++i) {
        ans *= i;
    } 
    for(int i = 1 ; i <= n-m ; ++i) {
        ans /= i;
    }
    return ans;
}

int main() {
    //int n;
    //cin >> n;
    for(int i = 0 ; i <= top ; ++i) {
        ll a = 0;
        for(int j = 0 ; j <= i ; ++j) {
            a += f(j) * pow(-1,i-j) * C(i,j);  
        }
        cout << a << endl;
    }

    return 0;
}