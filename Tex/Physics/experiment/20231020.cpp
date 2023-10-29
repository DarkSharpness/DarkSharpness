#include <iostream>
// #include <bits/stdc++.h>

double a[2] = {
    3.2648e-1,
    3.1025e-1
};
double b[2] = {
    -1.8067e-5,
    -1.7608e-5
};

template <int n>
double val(double x) { return a[n] + b[n] * x; }

signed main() {
    // double x = 462.0;
    // std::cout << val <0> (x) - val <1> (x) << '\n';
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    int x;
    double y;
    while(std::cin >> x >> y)
        std::cout << x << '\t' << y << '\n';
    return 0;
}