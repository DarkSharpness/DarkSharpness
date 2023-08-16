#include <iostream>
using namespace std;
const int N = 1e5 + 2;
int cnt[N];

signed main() {
    int n,c;
    scanf("%d%d",&n,&c);
    for(int i = 1,x ; i <= n ; ++i) {
        scanf("%d",&x);
        ++cnt[x];
    }
    long long ans = 0;
    for(int i = max(c - N,0) + 1 ; i < min(c / 2,N) ; ++i)
        ans += (long long)(cnt[i]) * cnt[c - i];
    printf("%lld\n",ans);
    return 0;
}
