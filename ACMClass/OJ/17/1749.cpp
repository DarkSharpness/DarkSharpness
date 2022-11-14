#include<bits/stdc++.h>
using namespace std;

const auto func = [](const int &n) -> void {
    bitset <20> b,c,d,a[20];
    int I[20];
    // 0 : 回溯状态
    // 1 : 向下递归
    // 2 : 向下递归(临时)
    int command = 1;
    int j = 0;
    while(j != -1) {
        if(j == n) {
            for(int i = 0 ; i < n ; ++i) { 
                for(int k = 0 ; k < n ; ++k)
                    putchar(a[k][i] ? 'Q' : '.');
                putchar('\n');
            }
            --j;
            command = 0;
        }
        int i = 0;
        if(!command) {
            a[I[j]][j] = b[I[j]] = c[I[j]+j] = d[I[j]-j+n] = false;
            i = I[j] + 1;
            command = 1;
        }
        for(; i < n; ++i) {
            if(b[i] || c[i+j] || d[i-j+n]) continue;
            a[i][j] = b[i] = c[i+j] = d[i-j+n] = true;
            I[j] = i;
            ++j;
            command = 2;
            break;
        }
        if(command == 2) command = 1;
        else         --j,command = 0;
    }
};


int main() {
    int n;
    cin >> n;
    func(n);
    return 0;
}