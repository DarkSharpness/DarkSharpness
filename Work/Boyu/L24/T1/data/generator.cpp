#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int N = 1024;

string generate(int n) {
    string str;
    str.resize(n);
    while(n--) { str[n] = rand() % 26 + 'a'; }
    return str;
}

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 9 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const int n = i * i * 4;
        auto head = generate(rand() % n);
        auto temp = head + generate(n) + head;
        freopen(in.data(),"w",stdout);
        std::cout << temp;
        freopen(out.data(),"w",stdout);
        char *str = temp.data();
        long ans = 0;
        for(int i = temp.size() - 1 ; i > 0 ; --i)
            if(!strncmp(str,str + temp.size() - i,i)) {
                ans = i;
                break;
            }
        if(ans) std::cout << temp.substr(0,ans);
        else    std::cout << '0';
    }
    return 0;
}