#include <iostream>
using namespace std;
using ll = long long;

ll gcd(ll x,ll y) { return y ? gcd(y,x % y) : x; }

signed main() {
    int n;
    cin >> n;
    ll x = 0,y = 1;
    while(n--) {
        char opt;
        ll a,b;
        cin >> opt >> a >> b;
        switch(opt) {
            case '-': a = -a; /* 把减法转化为加法 */
            case '+': {
                /* 处理掉分母的负号 */
                if(b < 0) b = -b,a = -a;
                ll c = x * b + y * a,
                          d = b * y;
                ll t = gcd(abs(c),d);
                x = c / t, y = d / t;
                break;
            }
            case '/': swap(a,b); /* 把除法转换为乘法 */
            case '*': {
                /* 处理掉分母的负号 */
                if(b < 0) b = -b,a = -a;
                x *= a , y *= b;
                ll t = gcd(abs(x),y);
                x /= t , y /= t;
                break;
            }
        }
    }
    cout << x << ' ' << y << '\n';
    return 0;
}
