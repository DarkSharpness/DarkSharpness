#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>

const double EPS = 1e-9;
struct point {
    double x, y;
    point operator+(point rhs) const {
        return (point){x + rhs.x, y + rhs.y};
    }
    point operator-(point rhs) const {
        return (point){x - rhs.x, y - rhs.y};
    }
    point operator*(double rhs) const {
        return (point){x * rhs, y * rhs};
    }
    double len() const {
        return sqrt(x * x + y * y);
    }
};
int sgn(double x) {
    if (x < -EPS) return -1;
    if (x > EPS) return 1;
    return 0;
}
double det(point x, point y) {
    return x.x * y.y - x.y * y.x;
}
double dot(point x, point y) {
    return x.x * y.x + x.y * y.y;
}
double dis(point x, point y) {
    return (x - y).len();
}
struct circle {
    point c;
    double r;
};
bool in_circle(point p, circle c) {
    return sgn(c.r - (c.c - p).len()) >= 0;
}
circle make_circle(point x, point y) {
    return (circle){(x + y) * 0.5, (x - y).len() * 0.5};
}
circle make_circle(point x, point y, point z) {
    point p = y - x, q = z - x, s = (point){dot(p, p) * 0.5, dot(q, q) * 0.5};
    double d = 1.0 / det(p, q);
    p = (point){det(s, (point){p.y, q.y}), det((point){p.x, q.x}, s)} * d;
    return (circle){x + p, p.len()};
}

const int N = 1e5 + 3;
point p[N];


double brutal(int n) {
    double ans = 0;
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++) {
            circle c = make_circle(p[i], p[j]);
            ans = std::max(ans, c.r);
        }

    for (int i = 1; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k <= n; k++) {
                circle c = make_circle(p[i], p[j], p[k]);
                if (sgn(dot(p[j] - p[i], p[k] - p[i])) < 0) c = make_circle(p[j], p[k]);
                if (sgn(dot(p[i] - p[j], p[k] - p[j])) < 0) c = make_circle(p[i], p[k]);
                if (sgn(dot(p[i] - p[k], p[j] - p[k])) < 0) c = make_circle(p[i], p[j]);
                ans = std::max(ans, c.r);
            }
    return ans;
}


signed main() {
    int n;
    srand(time(NULL));
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);    
    std::cin >> n;
    for(int i = 1 ; i <= n ; ++i)
        std::cin >> p[i].x >> p[i].y;

    // std::random_shuffle(p + 1, p + 1 + n);

    std::sort(p + 1,p + 1 + n, [](point x,point y) {
        return 2 * x.x + x.y < 2 * y.x + y.y;
    });

    while(n > 500) {
        const circle c = make_circle(p[1],p[n]);
        int w = 1;
        for(int t = 2 ; t < n ; ++t)
            if (!in_circle(p[t],c)) p[++w] = p[t];
        if (w == n - 1) std::random_shuffle(p + 1, p + 1 + n);
        else { p[++w] = p[n]; n = w; }
    }

    std::cout << std::fixed << std::setprecision(12) << brutal(n) << std::endl;
    return 0;
}
