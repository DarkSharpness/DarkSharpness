#include <bits/stdc++.h>
using namespace std;

const int N = 5003;
priority_queue <long long,vector <long long>, greater <long long> > q;

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const int m = 50 * i * i;
        const int n = rand() % m + 1;
        freopen(in.data(),"w",stdout);
        std::cout << n << '\n';
        for(int i = 0 ; i < n ; ++i) {
            int x = (rand() ^ (rand () << 5)) % m + 1;
            std::cout << x << ' ';
            q.push(x);
        }
        freopen(out.data(),"w",stdout);

        long long ans = 0;
        long long tmp = INT32_MAX;
        while(q.size() != 1) {
            int x = q.top(); q.pop();
            int y = q.top(); q.pop();
            ans += x + y;
            q.push(x + y);
            if (ans > tmp) {
                std::cerr << "Haha\n";
                tmp = INT64_MAX;
            }
        }
        q = decltype(q) {};
        std::cout << ans << '\n';
    }
    return 0;
}
