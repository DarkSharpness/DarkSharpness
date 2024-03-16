#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

using ll = long long;
int n,m,a,b,c,d;
const int N = 3004;

int s[N][N];

int small(int x,int y) {
    return s[x][y] + s[x - c][y - d]
         - s[x - c][y] - s[x][y - d];
}

int big(int x,int y) {
    return s[x][y] + s[x - a][y - b]
         - s[x - a][y] - s[x][y - b];
}

struct queue {
    int head;
    int tail;
    int data[N];
    queue() : head(0),tail(0) { memset(data,0,sizeof(data));}
    void push_back(int x) { data[++tail] = x; }
    void pop_front() { ++head; }
    void pop_back() { --tail; }
    bool size() { return head != tail;}
    int f() { return data[head + 1]; }
    int b() { return data[tail]; }
    void init() { head = tail = 0; }
};
queue q[N];


int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> a >> b >> c >> d;
    for(int i = 1 ; i <= n ; ++i)
        for(int j = 1 ; j <= m ; ++j) {
            cin >> s[i][j];
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        }
    int A = a - c - 1;
    int B = b - d - 1;
    if(n > 50 || m > 50) {
        queue Q;
        int ans = 0;
        for(int i = c ; i < n ; ++i) {
            Q.init();
            // min { i - A ~ i - 1 }
            for(int j = d ; j < m ; ++j) {

                while(q[j].size() && q[j].f() + A < i)
                    q[j].pop_front();
                while(q[j].size() && small(i,j) <= small(q[j].b(),j))
                    q[j].pop_back();
                q[j].push_back(i);

                while(Q.size() && Q.f() + B < j)
                    Q.pop_front();
                while(Q.size() && small(q[j].f(),j)
                            <= small(q[Q.b()].f(),Q.b()))
                    Q.pop_back();
                Q.push_back(j);

                if(i >= a - 1 && j >= b - 1) {
                    int t = Q.f();
                    ans = max(ans,big(i + 1,j + 1) - small(q[t].f(),t));
                }
            }
        }
        cout << ans;
    } else {
        int ans = 0;
        for(int i = a ; i <= n ; ++i)
            for(int j = b ; j <= m ; ++j) {
                int minn = 1 << 30;
                for(int k = i - a + c + 1 ; k < i ; ++k)
                    for(int l = j - b + d + 1 ; l < j ; ++l)
                        minn = min(minn,small(k,l));
                ans = max(ans,big(i,j) - minn);
            }
        cout << ans ;
    }
    return 0;
}