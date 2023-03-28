// #include <iostream
#include <Dark/inout>
#include <thread>

void test1() { dark::writeline("Fuck you World!"); }
void func(int a) { dark::printline("Integer:",a); }

signed main() {
    int a = 0;
    // std::thread th0(test1);
    std::thread th1 = std::thread(func,std::ref(a));
    a = 2;
    th1.join();

    
    // th0.join();
    return 0;
}
