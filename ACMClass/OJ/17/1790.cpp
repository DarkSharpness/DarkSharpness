#include <iostream>
#include <unordered_set>
using namespace std;
using ull = unsigned long long;

const int N = 1e6 + 7;
const ull b = 37;
char c[N];
ull h[N]; /* h */
ull p; /* Pow */
int n,m;

void prework() {
    p = 1;
    for(int i = 0 ; i < m ; ++i) p *= b;
    h[0] = c[0] - 'a';
    for(int i = 1 ; i < n ; ++i) h[i] = h[i - 1] * b + c[i] - 'a';
}

unordered_set <ull> u;

/* Hash value of : substr(x + 1 ~ x + m)  */
inline ull value(int x) { return h[x + m] - h[x] * p; }

signed main() {
    scanf("%d%d",&n,&m);
    scanf("%s",c);
    prework();
    u.insert(h[m - 1]);
    u.reserve(n - m);
    for(int i = 0 ; i < n - m; ++i) u.insert(value(i));
    printf("%llu",u.size());
    return 0;
}
