#include <bits/stdc++.h>
using namespace std;


const double dt = 0.001;
const double dw = 0.001;
const double w  = 2 * acos(-1); /* 2 * pi */
const double b1 = 0.1 * w; /* Note that b1 < w */
const double b2 = 2  * w; /* Note that b2 > w */
const double A  = 1.0;

const double B[8] = {
    0.1 * w,
    0.2 * w,
    0.3 * w,
    0.5 * w,
    0.7 * w,
    1 * w,
    2 * w,
    10 * w
};


signed main() {
    /* Under-damping. */
    freopen("a.tmp","w",stdout);
    for(int i = 0 ; i < 10000 ; ++i) { 
        double t = dt * i;
        double x = A * exp(-b1 * t) * cos(sqrt(w * w - b1 * b1) * t);
        std::printf("%.3lf\t%.8lf\n",t,x);
    }

    /* Over-damping */
    freopen("b.tmp","w",stdout);
    for(int i = 0 ; i < 10000 ; ++i) { 
        double t = dt * i;
        double x = A * exp(-b2 * t) * cosh(sqrt(b2 * b2 - w * w) * t);
        std::printf("%.3lf\t%.8lf\n",t,x);
    }

    freopen("c.tmp","w",stdout);
    for(int i = 0 ; i < 5000 ; ++i) {
        double w1 = dw * i * w;
        std::printf("%.3lf",dw * i);
        for(int j = 0 ; j < 8 ; ++j) {
            double b = B[j];
            double x = A / sqrt(pow((w * w - w1 * w1),2) + 4 * b * b * w1 * w1);
            std::printf("\t%.8lf",x);
        }
        puts("");
    }
    return 0;
}