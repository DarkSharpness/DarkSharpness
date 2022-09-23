#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pii;
#define IOS ios::sync_with_stdio(0)
#define For(i,a,b) for (int i=(a),_b=(b);i<=_b;i++)
#define FOr For
#define Iter(i,a,b) for (int i=(a),_b=(b);i<_b;i++)
#define Downto(i,a,b) for (int i=(a),_b=(b);i>=_b;i--)
#define set0(a) memset(a,0,sizeof(a))
#define set0n(a,n) memset(a,0,sizeof((a)[0])*(n+1))
#define pb push_back
#define mkp make_pair
#define all(a) (a).begin(),(a).end()
template <class T1,class T2>
inline void getmin(T1& x,const T2& y){if (y<x) x=y;}
template <class T1,class T2>
inline void getmax(T1& x,const T2& y){if (x<y) x=y;}
//char NY[2][10]={"NO\n","YES\n"};//capital?

#ifdef DEBUG
#define SHOW(x) (cerr<<#x"="<<(x)<<endl,(x))
#define MSG(s) (cerr<<"MESSAGE: "<<(s)<<endl,0)
#else
#define SHOW(x) (x)
#define MSG(s) 0
#endif

constexpr int N = 8e4+8;
//const int N=2e4+5;
int fa[N],sz[N];
int find(int x){return fa[x]==x?x:(fa[x]=find(fa[x]));}
inline void merge(int x,int y){
	x=find(x),y=find(y);
	fa[x]=y,sz[y]+=sz[x];
}
vi a;

bitset<N> f[2];

signed main(){
	IOS;
	int n,m,e;
	cin>>n>>m>>e;
	iota(fa+1,fa+1+n,1);
	fill(sz+1,sz+1+n,1);    
    double ti = clock();
    For(i,1,e){
		int x,y;cin>>x>>y;
		merge(x,y);
	}	
	For(i,1,n) if (fa[i]==i) a.pb(sz[i]);
	f[1][0]=1;
	int nn=a.size()-1;
	For(i,0,nn){
		f[i&1]=f[~i&1]|f[~i&1]<<a[i];
	}
	int ans=0;
	For(i,1,n) if (f[nn&1][i]&&abs(i-m)<abs(ans-m)) ans=i;
	cout<<ans<<endl;
	cout<<clock()-ti<<endl;
	return cout<<flush,0;
}