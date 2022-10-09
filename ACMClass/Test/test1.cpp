#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

unordered_multiset<int>s;
int main() {
    int n;
    cin >> n;
    while(n--) {
        int x;
        cin >> x;
        s.insert(x);
    }
     for(auto iter : s) {
        cout << iter << endl;
    }
    return 0;
}