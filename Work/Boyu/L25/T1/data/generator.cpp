#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

string generate(int n) {
    string str;
    str.resize(n);
    while(n--) { str[n] = rand() % 26 + 'a'; }
    return str;
}

string str[103];

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const int n = rand() % 100 + 1;
        const int m = rand() % 64  + 1;
        for(int i = 0 ; i < n ; ++i)
            str[i] = generate(m);
        freopen(in.data(),"w",stdout);
        std::cout << n << '\n';
        for(int i = 0 ; i < n ; ++i)
            std::cout << str[i] << '\n';
        freopen(out.data(),"w",stdout);
        sort(str,str + n);
        reverse(str,str + n);
        str[0].reserve(m * n + 1);
        for(int i = 1 ; i < n ; ++i)
            str[0] += str[i];
        std::cout << str[0] << '\n';
    }
    return 0;
}