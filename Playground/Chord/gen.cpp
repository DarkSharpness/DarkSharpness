#include <iostream>
#include <fstream>
// #include <bits/stdc++.h>

struct point { int x,y; };

const int n = 64;

int encode(point p) {
    return p.x * n + p.y;
}

point decode(int x) {
    return {x / n, x % n};
}

signed main() {
    std::ofstream fout("chord.tmp");
    fout << n * n << ' ';
    int cnt = 0;
    for (int i = 0 ; i < n * n ; ++i) {
        point p = decode(i);
        if (p.x >= p.y) continue;
        cnt += n - p.y - 1;
    }
    fout << cnt << std::endl;
    for (int i = 0 ; i < n * n ; ++i) {
        point p = decode(i);
        if (p.x >= p.y) continue;
        for (int j = p.y + 1 ; j < n ; ++j) {
            fout << i + 1 << ' ' << encode({p.y, j}) + 1 << std::endl;
        }
    }
    return 0;
}