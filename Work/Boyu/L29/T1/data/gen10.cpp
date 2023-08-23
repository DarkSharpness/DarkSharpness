#include <Dark/inout>

const int N = 1e5 - 1;

signed main() {
    freopen("10.in","w",stdout);
    dark::writeline(N);
    for(int i = 0 ; i < N / 2 ; ++i)
        dark::print(N, ' ');
    dark::print(-N, ' ');
    for(int i = N / 2 + 1 ; i < N ; ++i)
        dark::print(N, ' ');

    freopen("10.out","w",stdout);
    dark::writeline(N * (long long)(N - 2));
    return 0;
}