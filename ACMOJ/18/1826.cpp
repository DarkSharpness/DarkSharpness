#include <iostream>

const int N = 1000;
using namespace std;

struct tree {
    int left;
    int right;
    int v;
} ts[N];

int work(int x) {
    if(~x) return 0;
    return work(ts[x].left) + work(ts[x].right) + ts[x].v;
}

int sum() {
    int ans = 0;
    int  x  = 0;
    while(x != -1) {
        int p = ts[x].left;
        if(p == -1) {
            ans += ts[x].v;
            x = ts[x].right;
            continue;
        }
        while(ts[p].right != -1 && ts[p].right != x) p = ts[p].right;
        if(ts[p].right == -1) {
            ts[p].right = x;
            x = ts[x].left;
        } else {
            ts[p].right = -1;
            ans += ts[x].v;
            x = ts[x].right;
        }
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> ts[i].left;
        cin >> ts[i].right;
        cin >> ts[i].v;
    }
    cout << sum();
}