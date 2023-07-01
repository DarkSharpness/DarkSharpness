#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
#include "sort.hpp"
#else
int query(int x,int y) {return x < y;}
#endif

std::vector<int> my_sort(int n) {
    srand(time(NULL));
    std::vector <int> t(n);
    std::iota(t.begin(),t.end(),0);
    std::random_shuffle(t.begin(),t.end());

    const int N = n >> 1;

    std::vector <int> v = {t[0]};
    for(int i = 1 ; i < N ; ++i) {
        auto iter = std::lower_bound(v.begin(),v.end(),t[i],query);
        v.insert(iter,t[i]);
    }

    std::vector <int> w = {t[N]};
    for(int i = N + 1 ; i < n ; ++i) {
        auto iter = std::lower_bound(w.begin(),w.end(),t[i],query);
        w.insert(iter,t[i]);
    }

    t.clear();
    auto iter1 = v.begin(),
         iter2 = w.begin();
    while(iter1 != v.end() && iter2 != w.end()) {
        int cmp = query(*iter1,*iter2);
        if(cmp) t.push_back(*iter1++);
        else    t.push_back(*iter2++);
    }
    while(iter1 != v.end()) t.push_back(*iter1++);
    while(iter2 != w.end()) t.push_back(*iter2++);
    return t;
}

signed main() {
    auto vec = my_sort(10);
    for(auto iter : vec)
        std::cout << iter << '\n';
    return 0;
}