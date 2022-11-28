#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

inline void print(double X) {
    if(X < 0) {X = -X;cout << '-';}
    long long ans = X * 100 + 0.5;
    cout << ans / 100 << '.' << (ans / 10) % 10 << ans % 10 << '\n';
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
    void getAnswer() {
        constexpr double eps = 1e-5;
        Matrix &X = *this;
        for(size_t i = 0 ; i < row ; ++i) {
            size_t k = i;
            while(k < row) {
                if(fabs(X[k][i]) > eps) break;
                ++k;
            }
            if(k == row) {puts("No Solution");return;}
            if(k != i) for(size_t j = i ; j < col ; ++j) swap(X[i][j],X[k][j]);
            for(size_t j = 0 ; j < i ; ++j) {
                double ret = X[j][i] / X[i][i];
                X[j][i] = 0;
                if(fabs(ret) < eps) continue;
                for(size_t k = i + 1 ; k < col ; ++k) {
                    X[j][k] -= ret * X[i][k];
                }
            }
            for(size_t j = i + 1; j < row ; ++j) {
                double ret = X[j][i] / X[i][i];
                X[j][i] = 0;
                if(fabs(ret) < eps) continue;
                for(size_t k = i + 1 ; k < col ; ++k) {
                    X[j][k] -= ret * X[i][k];
                }
            }
        }
        for(size_t i = 0 ; i < row ; ++i) {
            print(X[i][row] / X[i][i]);
        }
    }

    Matrix(size_t _col,size_t _row) {
        data.resize((col = _col) * (row = _row));
    }
};

signed main() {
    int n;
    ios::sync_with_stdio(false);
    cin >> n;
    Matrix M(n + 1,n);
    for(int i = 0 ; i < n * (n + 1) ; ++i) cin >> M.data[i];
    M.getAnswer();
    return 0;
}