#include <iostream>
#include <cstdio>

using namespace std;

const int N = 1e4 + 1;

int n, m, u, v, lab[N], p[N];
bool c[N][N], vis[N];

inline void mcs()
{
	for (int i = n; i >= 1; --i)	
	{
		u = 0;
		for (int j = 1; j <= n; ++j)
			if (!vis[j] && (!u || lab[j] > lab[u]))
				u = j;
		vis[u] = 1;
		p[i] = u;
		for (int j = 1; j <= n; ++j)
			if (!vis[j] && c[u][j])
				++lab[j];
	}
}

int main() { 
    freopen("chord.tmp", "r", stdin);
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= m; ++i)	
	{
		cin >> u >> v;
		c[u][v] = c[v][u] = 1;
	}
	mcs();
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		ans = max(ans, lab[i] + 1);
	cout << ans << endl;
	return 0;
}