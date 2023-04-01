#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

unordered_set <string> s;
#define endl '\n'

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    s.reserve(10002);
    int ans = 0;
    string str;
    while(n--) {
        cin >> str;
        if(s.insert(str).second == true) 
            ++ans;
    }
    cout << ans << endl;

    return 0;
}