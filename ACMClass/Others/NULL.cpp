#include <iostream>
#include <algorithm>
using namespace std;

const int M = 1e3 + 4,N = 1e4 + 4;

#define int long long

struct item {
    int w,v;
    inline bool operator < (const item &B) {
        return w * B.v < v * B.w;
    }
}w[M];


int dp[N]; // dp[i][j] ��ʾ�Ѿ���������Ʒ 0 ~ i-1 �ռ�ʣ�� j �����Ž�
          // ��ʵ��,���ǲ�������ʷ��Ϣ,ÿ��dp����������ת��
          // ���Կ���ʡ�Ե�һά������.
signed main() {
    int n,m;
    ios::sync_with_stdio(false); // �ر���ͬ�� �����������
    cin >> n >> m;
    for(int i = 0 ; i < m ; ++i) cin >> w[i].v;
    for(int i = 0 ; i < m ; ++i) cin >> w[i].w;
    sort(w,w+m);
    // dp[0][n] = 0; // ��ʵ���ó�ʼ��
    for(int i = 0 ; i < m ; ++i) {        
        for(int j = w[i].w ; j <= n ; ++j) {
            // ��Ϊʡ�˵�һά,���Ա����С����ö��
            // �ұߵ�dp[j] ��ʵ��dp[i][j]
            // �Ǵ� j�ϴ� ���� j��С ��dp���
            // ����Ϊ�˱�֤�ڹ����� dp[i][j] �����bug,��С����ö��
            dp[j - w[i].w] = max(dp[j - w[i].w],dp[j] + j * w[i].v);
        }
    }
    int ans = 0;
    for(int i = 0 ; i <= n ; ++i) {
        if(dp[i] > ans) ans = dp[i];
    }
    cout << ans;
    return 0;
}