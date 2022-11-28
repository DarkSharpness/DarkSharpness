#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long
/// @brief Read an unsigned integer.
/// @param dst Where the unsigned integer will be written into.
template <class integer>
integer read() {
    integer dst;
    int  ch;
    while(!isdigit(ch = getchar()) && ch != EOF);
    dst = 0;
    while(isdigit(ch)) {
        dst = dst * 10 + (ch ^ '0');
        ch  = getchar();
    }
    return dst;
}
//#define int lont long
/// @brief Read an unsigned integer.
/// @param dst Where the unsigned integer will be written into.
template <class integer>
integer &read(integer &dst) {
    int  ch;
    while(!isdigit(ch = getchar()) && ch != EOF);
    dst = 0;
    while(isdigit(ch)) {
        dst = dst * 10 + (ch ^ '0');
        ch  = getchar();
    }
    return dst;
}


/**
 * @brief  Print out integer fast.
 * 
 * @tparam integer Any integer type. You may leave it blank
 *         or set the integer type yourself. For example, 
 *         Fwrite <unsigned> (-1) will be 4294967295.
 *
 * @param  src The number to be written.
 */
template <class integer>
void write(integer src) {
    static char ch[20];
    if(src == 0) {
        putchar('0');
    } else if(src < 0) {
        src = -src;
        putchar('-');
    }
    int32_t top = 19;
    while(src) {
        ch[--top] = (src % 10) ^ '0';
        src /= 10;
    }
    printf("%s",ch + top);
}

struct Matrix {
  public:
    vector <double> data;
    size_t col,row;
    inline double *operator [](size_t __n) {
        return &data[__n * col];
    }
    inline const double *operator [](size_t __n) const{
        return &data[__n * col];
    }
    size_t rank() {
        constexpr double eps = 1e-6;
        Matrix &X = *this;
        size_t cnt = 0;
        for(size_t i = 0 ; i < col ; ++i) {
            size_t k = cnt;
            while(k < row) {
                if(fabs(X[k][i]) > eps) break;
                ++k;
            }
            if(k == col) {continue;}
            if(k != cnt) for(size_t j = i ; j < col ; ++j) swap(X[cnt][j],X[k][j]);
            for(size_t j = cnt + 1; j < row ; ++j) {
                double ret = X[j][i] / X[cnt][i];
                X[j][i] = 0;
                for(size_t k = i + 1 ; k < col ; ++k) {
                    X[j][k] -= ret * X[cnt][k];
                }
            }
            ++cnt;
        }
        return cnt;
    }

    Matrix(size_t _col,size_t _row) {
        data.resize((col = _col) * (row = _row));
    }
};
const int N = 1007;
size_t rk[N];
size_t id[N];

signed main() {
    size_t m,n;
    read(m);read(n);
    Matrix M(n,n);
    for(size_t i = 0 ; i < m ; ++i) {
        for(size_t j = 0 ; j < n * n ; ++j)
            M.data[j] = read<int>();
        rk[i] = M.rank();
    }
    iota(id,id + m,0);
    m = unique(id,id + m,[](size_t x,size_t y)->bool{return rk[x] == rk[y];}) - id;
    write(m);putchar('\n');
    for(size_t i = 0 ; i < m ; ++i) {write(id[i] + 1);putchar(' ');}
    return 0;
}