#include "src.hpp"
#include <iostream>

struct koishi { int id; };

std::ostream &operator << (std::ostream &os, const koishi &k) {
    return os << "Komeiji Koishi " << k.id ;
}

void test0() {
    using sjtu::unique_ptr;
    unique_ptr <int> ptr1(new int(114514));

    // 移交所有权
    unique_ptr <int> ptr2(std::move(ptr1));

    // 释放所有权
    int *tmp = ptr2.release();
    delete tmp;
}


void test1() {
    using sjtu::unique_ptr;
    unique_ptr <koishi> ptr1 = sjtu::make_unique <koishi> (koishi(1));

    // 成员访问
    ptr1->id = 514;

    // 解引用
    std::cout << *ptr1 << std::endl;

    // 重置，现在 ptr1 应该为空
    ptr1.reset();
    if (!ptr1.get()) {
        std::cout << "ptr1 is empty!" << '\n';
    }
}


signed main() {
    test0();
    test1();    
    return 0;
}
