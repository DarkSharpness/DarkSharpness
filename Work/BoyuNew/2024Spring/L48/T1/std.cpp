#include <iostream>

// First 是一个指向数组首元素的指针
// Last 是一个指向数组尾元素后面一个位置的指针
int finding(int *first, int *last, int val) {
    int l = 0;
    int r = last - first;
    while (l != r) {
        int mid = (l + r) / 2;
        if (first[mid] < val) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return first[l];
}

signed main() {
    int n, m;
    std::cin >> n >> m;
    int *a = new int[n];
    for (int i = 0; i < n; i++) std::cin >> a[i];
    while (m--) {
        int x;
        std::cin >> x;
        std::cout << finding(a, a + n, x) << '\n';
    }
    return 0;
}
