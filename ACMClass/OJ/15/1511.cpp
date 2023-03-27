#include <iostream>
#include <Dark/inout>

using ll = long long;
const ll N = 1e6+10;
ll sum[N],num[N],n,c[N],x[N];
ll head = 1,tail = 1,q[N],f[N];

inline double slope(ll i,ll j) noexcept
{ return double(f[j] + sum[j] - f[i] - sum[i]) / (num[j] - num[i]); } 


signed main() {
    dark::read_u(n);
	for(int i = 1 ; i <= n; ++i) {
        dark::read_u(x[i],num[i],c[i]);
		sum[i] =  sum[i-1] + x[i] * num[i]; 
		num[i] += num[i-1];
	}
	for(int i = 1 ; i <= n ; ++i) {
		while(head != tail && slope(q[head],q[head+1]) <= x[i])
            ++head;
		int j = q[head];
		f[i] = f[j] - sum[i] + sum[j] + (num[i] - num[j]) * x[i] + c[i];

		while(head != tail && slope(q[tail - 1],q[tail]) > 
                              slope(q[tail],i))
            --tail;
		q[++tail]=i;
	}
    int i = n;
    ll ans = f[n];
    while(num[i] - num[i - 1] == 0)
        if(ans > f[--i]) ans = f[i];
    printf("%lld",ans);
	return 0 ;
}

/* 

价格相当于先移到0再移到当前位置 
f[i] = f[j] - sum[i] + sum[j] + (num[i] - num[j]) * x[i] + c[i];
f[j] + sum[j] = x[i] * num[j] + f[i] + sum[i] - c[i] - num[i] * x[i]; 
k = x[i]; 单调
x = num[j]; 单调
y = f[j]+sum[j];

*/