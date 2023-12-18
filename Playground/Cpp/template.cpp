#include <iostream>

template <typename T>
concept NotAddable = !requires(T &a) { a += a; };

template <NotAddable T>
inline T &operator += (T &a, const T& b) { return a = a + b; }

struct tester {
    int x;
    tester operator + (const tester &b) const { return *this; }
};

signed main() {
    tester x;
    x += x; // Fail
    return 0;
}