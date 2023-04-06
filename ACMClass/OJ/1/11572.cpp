#include <bits/stdc++.h>
typedef long long ll ;
using namespace std ;
ll j , k , m , n , a , ans;
ll num[500010];
struct node
{
	ll loc,num;
}p[500010];

ll lowbit(int x)
{
	return x&(-x);
}


void Add(ll loc,ll x)
{
	ll b=loc;
	while(b<=m)
	{
		num[b]+=x;
		b+=lowbit(b);
	}
}

ll sum(int x)
{
	ll y = 0, numm=x;
	while(numm) {
		y+=num[numm];
		numm -= lowbit(numm);
	}
	return y ;
}

bool cmp(node a ,node b) {
	if(a.num != b.num) return a.num < b.num;
	else return a.loc < b.loc;
}



int main()
{
	scanf("%lld",&m);
	for(ll i=1 ; i<=m ; i++)
	{
		scanf("%lld",&a);
		p[i].loc=i;
		p[i].num=a;
	}
	sort(p+1,p+m+1,cmp);
	for(ll i=1 ; i<=m ; i++)
	{
		Add(p[i].loc,1);
		ans+=sum(p[i].loc-1);
	}
	printf("%lld",m*(m-1)/2-ans);
	return 0 ;
}