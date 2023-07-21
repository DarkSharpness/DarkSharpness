#include <iostream>
#include <algorithm>


struct node {
    int value;
    int index;
} a[1024];

// 只需要在值 value 相同的时候比较下标 index 即可
bool cmp(const node &lhs,const node &rhs) {
    if(lhs.value != rhs.value)
        return lhs.value < rhs.value;
    else
        return lhs.index < rhs.index;
}

signed main() {
    int n;
    std::cin >> n;
    for(int i = 0 ; i < n ; ++i) {
        a[i].index = i;
        std::cin >> a[i].value;
    }
    std::sort(a,a + n,cmp);
    for(int i = 0 ; i < n ; ++i)
        std::cout << a[i].index << ' ';
    return 0;
}

