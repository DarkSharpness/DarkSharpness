#include <bits/stdc++.h>
#define mid ((t[id].l + t[id].r) >> 1)
#define lc (id<<1)
#define rc (id<<1|1)
using namespace std ;
typedef long long ll ;
const int N = 100005;
ll a[N];
constexpr ll p = 1e9 + 7;
struct segtree
{
	ll l,r,s,a,m;
}t[N<<2];


void Pushup(ll id)
{
	t[id].s = (t[lc].s + t[rc].s)%p;
}

void Pushdown(ll id)
{
	t[lc].s=(t[id].m*t[lc].s+(t[lc].r-t[lc].l+1)*t[id].a)%p;
	t[lc].a=(t[lc].a*t[id].m+t[id].a)%p;
	t[lc].m=t[id].m*t[lc].m%p;
	t[rc].s=(t[id].m*t[rc].s+(t[rc].r-t[rc].l+1)*t[id].a)%p;
	t[rc].a=(t[rc].a*t[id].m+t[id].a)%p;
	t[rc].m=t[id].m*t[rc].m%p;
	t[id].a=0;
	t[id].m=1;
}

void Build(ll id,ll l,ll r)
{
	t[id].l = l;
	t[id].r = r;
	t[id].m = 1;
	if(l == r)
	{
		t[id].s = a[r]%p;
	}
	else
	{
		Build(lc,l,mid);
		Build(rc,mid+1,r);
		Pushup(id);
	}
}

void Update(ll id,ll l,ll r,ll k,bool F)
{
	if(l == t[id].l && r == t[id].r)
	{
		if(F)//F=1 加法 F=0 乘法 
		{
			t[id].s =(t[id].s+k*(t[id].r-t[id].l+1))%p;
			t[id].a =(t[id].a+k)%p; 
		}
		else
		{
			t[id].s=t[id].s*k%p;
			t[id].a=t[id].a*k%p;
			t[id].m=t[id].m*k%p;
		}
	}
	else
	{
		Pushdown(id);
		if(r <= mid) Update(lc,l,r,k,F);
		else if(l > mid) Update(rc,l,r,k,F);
		else
		{
			Update(lc,l,mid,k,F);
			Update(rc,mid+1,r,k,F);
		}
		Pushup(id);
	}
}

ll Query(ll id,ll l,ll r)
{
	if(l == t[id].l && r == t[id].r)
	{
		return t[id].s%p;
	}
	Pushdown(id);
	if(r <= mid) return Query(lc,l,r);
	else if(l > mid) return Query(rc,l,r);
	else
	{
		return (Query(lc,l,mid) + Query(rc,mid+1,r))%p;
	}
	Pushup(id); 
}

int main()
{
	ll n,m,j,x,y,z;
    ll P;
	scanf("%lld%lld",&n,&P);
	for(int i=1 ; i<=n ; i++ )
		scanf("%lld",a+i);
	Build(1,1,n);
    scanf("%lld",&m);
	for(int i=1 ; i<=m ; i++)
	{
		scanf("%lld%lld%lld",&j,&x,&y);
		if(j<=2) 
		{
			scanf("%lld",&z);
			Update(1,x,y,z%p,bool(j-1));
		}
		else 
		{
			printf("%lld\n",Query(1,x,y));
		}
	}
	return 0 ;			
}

