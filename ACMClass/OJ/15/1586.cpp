#include <iostream>
#include <cstring>
// #include <Dark/inout>
// #define int long long
// using ll = long long;
// using ull = unsigned long long;
using namespace std;

constexpr int N = 2023;
constexpr int M = 1e9 + 7;
char n[N];
int tot = 0;
int id[N][10];
int fail[N];

int qq[N],head = 0,tail = 0;
bool is[N]; /* Whether disabled. */

struct queue {
    int pop() const noexcept { return qq[head++]; }
    void push(int x) const noexcept { qq[tail++] = x;  }
    bool nempty() const noexcept { return head != tail; }
};

queue q;

int dp[N][N][2]; /* Length | Node | top-bit. */

/* Append y to x and avoid overflow. */
inline void ap(int &x,unsigned y) { x = (x + y) % M; }

inline void selfadd(int &x) { if(x == M - 1) {x = 0;} else {++x;} }


struct WA_Machine {
    void insert() const noexcept {
        char ch;
        int x = 0;
        while(!isdigit(ch = getchar()));
        while(isdigit(ch)) {
            int &t = id[x][ch - '0'];
            x = (t ? t : (t = ++tot));
            ch = getchar();
        }
        is[x] = true;
    }

    void buildWA() const noexcept {
        for(int i = 0 ; i < 10 ; ++i)
            if(id[0][i]) q.push(id[0][i]) , fail[id[0][i]] = 0;
        while(q.nempty()) {
            int x = q.pop();
            is[x] |= is[fail[x]];
            for(int i = 0 ; i < 10 ; ++i) {
                if(id[x][i]) q.push(id[x][i]),fail[id[x][i]] = id[fail[x]][i];
                else id[x][i] = id[fail[x]][i];
            }
        }
    }

    void work() const noexcept {
        int len = strlen(n + 1);

        int x = n[1] - '0';
        for(int k = 1,v ; k <= x ; ++k)
            if(!is[v = id[0][k]]) selfadd(dp[1][v][k == x]);

        for(int i = 2 ; i <= len ; ++i) { /* All lengths. */
            int x = n[i] - '0';

            for(int j = 0 ; j <= tot; ++j) { /* All nodes. */
                if(is[j]) continue;
                /* From not highest-bit. */
                for(int k = 0,v ; k <= 9 ; ++k)
                    if(!is[v = id[j][k]])
                        ap(dp[i][v][0],dp[i - 1][j][0]);

                /* From highest bit. */
                for(int k = 0,v ; k <= x ; ++k) 
                    if(!is[v = id[j][k]])
                        ap(dp[i][v][k == x],dp[i - 1][j][1]);
            }

            for(int k = 1,v ; k < 10 ; ++k)
                if(!is[v = id[0][k]]) selfadd(dp[i][v][0]);
        }

        int ans = 0;
        for(int j = 0 ; j <= tot ; ++j) 
            if(!is[j]) ap(ans,dp[len][j][0] + dp[len][j][1]);

        printf("%d",ans);
    }

} darksharpness;





signed main() {
    int m;
    scanf("%s%d",n + 1,&m);
    while(m--) darksharpness.insert();
    darksharpness.buildWA();
    darksharpness.work();
    return 0;

}
