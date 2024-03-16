#include <compare>
#include <iostream>
#include <cmath>
// #include <bits/stdc++.h>
// #include <Dark/inout>

struct B {
    friend bool operator == (const B &,const B &) {
        std::cout << "Equal!\n";
        return true;
    }
    
    // friend auto operator <=> (const B &,const B &) // = default;
    // {
    //     // std::cout << "3-way!\n";
    //     return std::strong_ordering::equal;
    // }
};


struct A {
    int x;
    long y;
    B z;

    friend auto operator <=> (const A &,const A &) = default;
};

struct C {
    double v {NAN};
    friend auto operator <=> (const C &,const C &) = default;
};

auto operator <=> (const A &x,int y)  { return x.x <=> y; }

signed main() {
    A test1{
        .x = 1,
        .y = 2,
        .z = {}
    },test2 {
        .x = 1,
        .y = 2,
        .z = {}
    };
    std::cout << (test1 == test2) << '\n';
    std::cout << std::is_eq(test1 <=> 2)<< '\n';    

    int x = 0;
    if(x) 
        int x = 0;


    return 0;
}
