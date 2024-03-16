#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

bool judge(ll id) {
    if(id < 10) {
        if(id == 4) return true;
        if(id == 7) return true;
        return false;
    }
    ll ret = id % 10;
    if(ret != 4 && ret != 7) return false;
    else return judge(id/10);
}


ll work(ll num) {
    if(num < 10) {
        if(num >= 7) return 2;
        if(num >= 4) return 1;
        return 0;
    }
    ll ret = num % 10;
    if(ret <= 3)
        return (work(num/10-1)+1)*2;
    if(ret <= 6) 
        return (work(num/10-1)+1)*2+judge(num/10);
    else 
        return (work(num/10-1)+1)*2+judge(num/10)*2;
}




ll p[100];
ll m[100];

ll gets(ll loc) {
    ll i = 1;
    while(1) {
        if(m[i]) --loc;
        if(!loc) break;
        ++i;
    } 
    return i;
}
ll Find(ll loc,ll nums,ll k) {
    if(nums == 1) return gets(1);
    ll ret = (k - 1) / p[nums-1] + 1;
    if(loc == 1)
        return gets(ret);
    else {
        m[gets(ret)] = 0;
        return Find(loc-1,nums-1,(k - 1) % p[nums-1] + 1);
    }
}

int main() {
    ll x,k;
    #define endl '\n'
    cin >> x >> k;
    p[1] = 1;
    for(ll i = 2; i <= 15 ; ++i) 
        p[i] = p[i-1] * i;
    if(x <= 11 && k > p[x]) {
        cout << "-1" << endl;
        return 0;
    }
    ll sum = 0;
    if(x > 14) {
        sum = work(x-13);
    } 
    ll l = max(1ll,x-12);
    ll cnt = 0;
    ll loc[2] = {0,0};
    for(ll i = l ; i <= x ; ++i) {
        if(judge(i)) loc[cnt++] = i - l + 1;
    }
    if(cnt == 0) {
    } else if(cnt == 1) {
        for(ll i = 1; i <= 20 ; ++i) m[i] = 1;
        if(Find(loc[0],x-l+1,k) == loc[0]) ++sum;
    } else {
        //cout << loc[0] << ' ' <<loc[1] << endl;
        for(ll i = 1; i <= 20 ; ++i) m[i] = 1;
        ll a = Find(loc[0],x-l+1,k);
        for(ll i = 1; i <= 20 ; ++i) m[i] = 1;
        ll b = Find(loc[1],x-l+1,k);
        if(a == loc[0] || a == loc[1]) ++sum;
        if(b == loc[0] || b == loc[1]) ++sum; 
    }
    cout << sum << endl;
    
    return 0;
}