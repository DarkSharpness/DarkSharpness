#include "src.hpp"
#include <iostream>
#include <vector>

struct tester { int x,y; };

signed main() {
    static_assert (sizeof(sjtu::unique_ptr <int>) == sizeof(int *), "unique_ptr should be the same size as a raw pointer");
    static_assert (!std::is_copy_constructible <sjtu::unique_ptr <int>>::value, "unique_ptr should not be copy constructible");
    static_assert (!std::is_copy_assignable <sjtu::unique_ptr <int>>::value, "unique_ptr should not be copy assignable");

    sjtu::unique_ptr <tester> ptr1(new tester {1,2});
    sjtu::unique_ptr <tester> ptr2(new tester {3,4});

    if (ptr1->x != 1 || ptr1->y != 2) std::exit(1);
    if (ptr2->x != 3 || ptr2->y != 4) std::exit(1);

    ptr1 = std::move(ptr2);
    if (ptr1->x != 3 || ptr1->y != 4) std::exit(1);
    ptr1.reset();
    if (ptr1.get() != nullptr) std::exit(1);

    for (int i = 0 ; i < 100 ; ++i) ptr1.release() , ptr2.release();
    std::cout << "Test passed!" << std::endl;
    return 0;
}
