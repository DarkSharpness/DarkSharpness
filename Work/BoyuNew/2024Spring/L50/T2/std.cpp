#include <iostream>
using namespace std;

const int N = 2e6 + 2;

long long q[N];
long long a[N];
int n;
int top = 0;
int head = 0, tail = 0;

long long get_min() {
    if (head == tail)   return a[top++];
    if (top == n)       return q[head++];

    if (a[top] < q[head])   return a[top++];
    else                    return q[head++];
}


signed main() {
    cin >> n;
    for (int i = 0 ; i < n ; ++i) cin >> a[i];
    for (int i = 1 ; i < n ; ++i) {
        long long z = get_min() + get_min();
        cout << z << ' ';
        q[tail++] = z;
    }
    return 0;
}
