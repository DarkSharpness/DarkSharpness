#include <bits/stdc++.h>
using namespace std;

template <class T = void>
struct custom_pointer { T *data; };

signed main() {
    void *ptr = custom_pointer <void> {nullptr}.data;
    if(ptr == nullptr) puts("1"); 
    return 0;
}