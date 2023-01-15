#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long


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

signed main() {


    return 0;
}