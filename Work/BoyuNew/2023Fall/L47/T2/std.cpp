#include <iostream>
using namespace std;

const int N = 1e5 + 3;
int cnt[N];

signed main() {
    int n;
    cin >> n;
    int first2 = 0;
    int last3 = 0;

    for (int i = 1 , a ; i <= n ; ++i) {
        cin >> a;
        cnt[i] = cnt[i - 1];
        if (a == 1) {
            ++cnt[i];
        } else if (a == 2) {
            if (first2 == 0)
                first2 = i;
        } else {
            last3 = i;
        }
    }

    int ans1 = cnt[n]; // 只有 1
    int ans2 = first2 ? cnt[n] - cnt[first2] + 1 : 0; // 1 和 2
    int ans3 = last3 ? cnt[last3] + 1 : 0; // 3
    int ans4 = first2 && last3 && first2 <= last3 ? cnt[last3] - cnt[first2] + 2 : 0; // 2 和 3

    cout << max(ans1, max(ans2, max(ans3, ans4))) << endl;
    return 0;
}