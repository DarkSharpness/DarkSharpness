#include <iostream>
using namespace std;


signed main() {
    long long y,m,t;
    double d;
    scanf("%lld%lld%lf%lld",&y,&m,&d,&t);
    if(y > t / (20 * 20 * 10000) ) {
        printf("Yes");
        return 0;
    } else if(y < t / (20 * 20 * 10000)) {
        printf("No");
        return 0;
    }
    t %= (20 * 20 * 10000);
    if(m > t / (20 * 10000)) {
        printf("Yes");
        return 0;
    } else if(m < t / (20 * 10000)) {
        printf("No");
        return 0;
    }
    t %= (20 * 10000);
    d *= 10000;
    if(d > t) {
        printf("Yes");
    } else {
        printf("No");
    }
    return 0;
}