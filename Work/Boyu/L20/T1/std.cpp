#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100;
int a[N];

int main() {
    int n;
    cin >> n;
    for(int i = 0 ; i < n ; ++i)
        cin >> a[i];
    int ans = 0;
    for(int i = 0 ; i < n ; ++i)
        for(int j = i + 1; j < n ; ++j)
            for(int k = j + 1 ; k < n ; ++k)
                if (a[i] + a[j] > a[k] &&
                    a[j] + a[k] > a[i] &&
                    a[k] + a[i] > a[j]) ++ans;
    std::cout << ans << '\n';
    return 0;
}