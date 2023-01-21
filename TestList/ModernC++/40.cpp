#include <bits/stdc++.h>

signed main() {

    std::atomic <int> ai(0);         //初始化ai为0
    ai = 10;                        //原子性地设置ai为10
    std::cout << ai;                //原子性地读取ai的值
    ++ai;                           //原子性地递增ai到11
    --ai;                           //原子性地递减ai到10

    return 0;
}