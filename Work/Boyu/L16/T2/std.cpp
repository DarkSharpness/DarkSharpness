#include <iostream>
using namespace std;

const int N = 103; // 保证输入长度不超过 100
struct node {
    int length;   // 长度
    int v[N];     // 数字

    // 输入
    void input() {
        for(int i = 1 ; i <= length ; ++i)
            cin >> v[i];
    }

    // 输出
    void find(int x) {
        int count = 0;
        for(int i = 1 ; i <= length ; ++i)
            if(v[i] == x) {
                ++count;
                cout << i << ' ';
            }
        if(count == 0) cout << 0;
        cout << '\n';
    }
} t;

int main() {
    int q;
    cin >> t.length >> q;
    t.input();
    while(q--) {
        int x;
        cin >> x;
        t.find(x);
    }
    return 0;
}