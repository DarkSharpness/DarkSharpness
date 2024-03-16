#include <iostream>
#include <Dark/inout>

const int N = 1e5 + 3;
int lg[N];
int dp[18][N];

int main() {
    int n,m;
    dark::read_u(n,m);

	for(int i = 1 ; i <= n ; i++) dark::read_u(dp[0][i]);

	for(int j = 1,len ; (len = 1 << j) <= n ; j++)
		for(int i = 1 ; i + len - 1 <= n ; i++)
			dp[j][i] = std::max(dp[j - 1][i],dp[j - 1][i + (len >> 1)]);
    
    for(int i = 2 ; i <= n ; ++i) lg[i] = lg[i - 1] + !(i & (i - 1));

	while(m--) {
		int l , r ;
        dark::read_u(l,r);
        int j = lg[r - l + 1];
        dark::writeline(std::max(dp[j][l],dp[j][r - (1 << j) + 1]));
	}
	return 0 ;
}