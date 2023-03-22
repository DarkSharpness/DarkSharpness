#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

int ran() { return abs(rand() << 16 | rand()); }

const int N = 1e6 + 2;
bitset <N> notprime;

vector <int> prime;

void pre() {
    for(size_t i = 2 ; i < N ; ++i) {
        if(!notprime[i]) prime.push_back(i);
        for(size_t j = 0 ; j != prime.size() && prime[j] * i < N ; ++j) {
            notprime[prime[j] * i] = true;
            if(i % prime[j] == 0) break;
        }
    }
}


signed main() {
    pre();
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        freopen(in.c_str(),"w",stdout);

        int x = (rand() % 3 == 0) ? prime[ran() % prime.size()] : (ran() % 999998 + 2);
        dark::write(x);

        freopen(out.c_str(),"w",stdout);

        dark::write(notprime[x] ? "No" : "Yes");
    }


    return 0;
}