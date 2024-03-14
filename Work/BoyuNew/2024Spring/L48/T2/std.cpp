#include <iostream>

int a[20][30][40];

signed main() {
    int cnt = 0;
    for (int i = 0 ; i < 20 ; ++i)
        for (int j = 0 ; j < 30 ; ++j)
            for (int k = 0 ; k < 40 ; ++k)
                a[i][j][k] = cnt++;

    int (*x)[30][40]    = &a[1];
    int (*y)[40]        = &a[5][6] + 1;
    int  *z             = &a[7][8][9];

    std::cout << (++x)[1][3][3] << std::endl;
    std::cout << (*(--y))[0] << std::endl;
    std::cout << z[3] << std::endl;
    return 0;
}
