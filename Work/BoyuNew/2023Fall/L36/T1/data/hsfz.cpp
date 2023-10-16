#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=5010;
int n,w,c,a[maxn],cnt[maxn],tot[maxn],ans;
int main()
{
	scanf("%d%d%d",&n,&w,&c);
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	for(int i=1;i<=n;i++)for(int j=1;j<n;j++)if(a[j]<a[j+1])swap(a[j],a[j+1]);
    if (a[1] > w) return puts("-1"), 0;

    for(int i=1;i<=n;i++)
	{
		int arg=0;
		for(int j=1;j<=ans;j++)if(cnt[j]==1&&tot[j]+a[i]<=w&&(!arg||tot[arg]<tot[j]))arg=j;
		if(!arg)ans++,cnt[ans]=1,tot[ans]=a[i];
		else cnt[arg]=2;
	}
    if (ans > c) puts("-1");
    else printf("%d\n",ans);
	return 0;
}