#include <iostream>

int a[20][30][40];

signed main() {
    int cnt = 0;
    for (int i = 0 ; i < 20 ; ++i)
        for (int j = 0 ; j < 30 ; ++j)
            for (int k = 0 ; k < 40 ; ++k)
                a[i][j][k] = cnt++;

    /**
     * 请你定义 x,y,z 三个变量
     * 使得下面的代码能够正常运行
     * 并且分别输出
     * - a[3][3][3] 的值
     * - a[5][6][0] 的值
     * - a[7][8][12] 的值
     */

    // 提示:
    //  - x 应该是一个指向二维数组的指针
    //  - y 应该是一个指向一维数组的指针
    //  - z 应该是一个指向 int 的指针

    std::cout << (++x)[1][3][3] << std::endl;
    std::cout << (*(--y))[-1] << std::endl;
    std::cout << z[3] << std::endl;
    return 0;
}
