#include <bits/stdc++.h>
using ull = unsigned long long;

const int N = 503;

size_t is_sqr2(ull x) {
    ull l = 1;
    ull r = 2e9;
    while(l != r) {
        ull mid = (l + r) >> 1;
        if(mid * mid > x) {
            r = mid;
        } else if (mid * mid < x) {
            l = mid + 1;
        } else {
            return mid;
        }
    } return 0;
}

size_t is_sqr3(ull x) {
    ull l = 1;
    ull r = 2e6;
    while(l != r) {
        ull mid = (l + r) >> 1;
        if(mid * mid * mid > x) {
            r = mid;
        } else if (mid * mid * mid < x) {
            l = mid + 1;
        } else {
            return mid;
        }
    } return 0;
}


struct node {
    ull num  = 0;
    ull x1   = 0;

    int work() {
        x1 = is_sqr2(num);
        if(x1) {
            ull y = is_sqr2(x1);
            if(y) {
                x1 = y;
                return 4;
            }
            else return 2;
        } else {
            x1 = is_sqr3(num);
            if(x1) return 3;
            else   return 0;
        }
    }

    void update(ull n) {
        if(x1) return;
        else x1 = n;
    }
} t[N];


std::unordered_map <ull,ull> prime;
std::vector <int> fuck;

void deal_fuck() {
    for(size_t x = 0 ; x != fuck.size() ; ++x) {
        auto i = fuck[x];
        for(size_t y = x + 1 ; y != fuck.size() ; ++y) {
            auto j = fuck[y];
            auto n = std::__gcd(t[i].num,t[j].num);
            if(n == 1) continue;
            // Have common divisor.
            t[i].update(n);
            t[j].update(n);
        }
    }
    size_t j = 0;
    for(auto i : fuck) {
        if(t[i].x1) {
            ++prime[t[i].x1];
            ++prime[t[i].num / t[i].x1];
        } else {
            fuck[j++] = i;
        }
    }
    fuck.resize(j);
}

void deal_prime() {
    size_t j = 0;
    for(auto i : fuck) {
        for(auto &&[n,cnt] : prime) {
            if(t[i].num % n == 0) {
                ++cnt;
                t[i].x1 = n;
                break;
            }
        }
        if(t[i].x1) ++prime[t[i].num / t[i].x1];
        else        ++j;
    }
    fuck.resize(j);
}

constexpr ull mod = 998244353;

signed main() {
    int n;
    std::cin >> n;
    fuck.reserve(n);
    for(int i = 0 ; i < n ; ++i) {
        std::cin >> t[i].num;
        auto cnt = t[i].work();
        if(cnt > 0) prime[t[i].x1] += cnt;
        else fuck.push_back(i);
    }
    deal_fuck();
    deal_prime();
    ull ans = 1;
    for(auto &&[n,cnt] : prime) {
        ans *= (cnt + 1);
        ans %= mod;
    }
    size_t cnt = fuck.size() << 1;
    while(cnt--) { ans <<= 1; if(ans > mod) ans -= mod; }
    std::cout << ans << '\n';
    return 0;
}
