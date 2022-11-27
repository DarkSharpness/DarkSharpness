#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long

unordered_map <std::string,int>mp;

signed main() {
    mp["1"] = 0;
    mp["2"] = 1;
    auto i = mp.insert(make_pair("2",114514));
    cout << i.second;
    for(auto it : mp){
        cout << it.second << '\n';
    }

    return 0;
}