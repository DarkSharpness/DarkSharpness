#include <iostream>
#include <cstring>

int n;
// д����������������
using intptr = int *;
using intptrptr = int **;
intptr &funA(intptrptr &ptr) {
    return (intptr&)(ptr);
}

void funB(intptr ans,intptrptr a,intptrptr b) {
    for(int i = 0 ; i < n ; ++i) {
        ans[i] = intptr(a)[i] * intptr(b)[i];
    }
}

int main() {
    int a[100], b[100], c[100];
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }
    int **p = nullptr;
    int **q = nullptr;
    funA(p) = a;
    funA(q) = b;
    funB(c, p, q);
    for (int i = 0; i < n; ++i) {
        std::cout << c[i] << " ";
    }
    return 0;
}

// д�����������Ķ���