#include <bits/stdc++.h>
using namespace std;

int a[20];

int sum(int n) {
    int val = 0;
    int tmp = 1;
    for (int i = 1 ; i <= n ; ++i) {
        val += (a[i] - 1) * tmp;
        tmp *= n;
    }
    return val;
}

void split(int val,int n) {
    for (int i = 1 ; i <= n ; ++i) {
        a[i] = val % n + 1;
        val /= n;
    }
}

struct state {
    int val, step;
};

const int N = 1e6 + 10;
bool vis[N];

signed main() {
    std::queue <state> q;
    state st;
    int n;

    cin >> n;
    for (int i = 1 ; i <= n ; ++i) cin >> a[i];

    st.val = sum(n);
    vis[st.val] = true;
    st.step = 0;
    q.push(st);

    for (int i = 1 ; i <= n ; ++i) cin >> a[i];
    const int val = sum(n);

    if (val == st.val) {
        cout << 0 << '\n';
        return 0;
    }

    split(val, n);

    while (!q.empty()) {
        st = q.front(); q.pop();

        int cur = st.val;
        ++st.step;

        split(cur, n);
        for (int i = 1 ; i <= n ; ++i)
            for(int j = i + 1 ; j <= n ; ++j) {
                swap(a[i], a[j]);
                int tmp = sum(n);
                if (vis[tmp]) continue;
                if (tmp == val) {
                    cout << st.step << '\n';
                    return 0;
                }
                st.val  = tmp;
                q.push(st);
                swap(a[i], a[j]);
            }
    }
    return 0;
}
