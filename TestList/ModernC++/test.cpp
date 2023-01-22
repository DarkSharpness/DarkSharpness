#include <bits/stdc++.h>

struct object {
    int data;
}a[10];

struct foo {
    foo() {}
    foo(const foo &) = default;
    foo(foo &&) noexcept {}

    foo &operator =(const foo &) = delete;
    foo &operator =(foo &&) noexcept {}
    ~foo() {}
};

struct test {
    int *ptr;
    test(int x = 2) : ptr(new int{x}) { std::cout << "Construction!\n"; }
    test(const test &rhs) : test(*rhs) {}
    int operator *(void) const {
        return *ptr;
    }

    void deal() &  {std::cout << "Lvalue" << *ptr << '\n';}
    void deal() && {std::cout << "Rvalue" << *ptr << '\n';}

    ~test() { std::cout << "Deconstruction\n"; delete ptr; ptr = nullptr; }
};


void func(object (&t)[10]) {
    if(t[0].data) {
        --t[0].data;
        ++t[1].data;
    }
}


signed main() {
    a[0].data = 10;
    func(a);
    std::cout << a[1].data << '\n';

    int iter = *std::vector <test>(3,1) [2];

    std::cout << iter << '\n';

    foo ________t = foo();


    std::map <int,int> mp;
    mp[0] = 1;
    mp[1] = 2;
    mp[3] = -1;
    auto &&tmp = *mp.begin();
    const_cast <int &> (tmp.first) = 2;
    for(auto &iter : mp) {
        std::cout << iter.first << ' ' << iter.second << '\n';
    }

    int &&X = 10;
    const decltype(X) Y = 1;

    
    test tt = test(10);
    tt.deal();
    test(3).deal();


    std::mutex m;
    return 0;
}
