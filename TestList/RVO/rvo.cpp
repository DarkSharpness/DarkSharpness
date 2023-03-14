/*
    Return value optimization.(RVO)
    Named return value optimization.(NRVO)
*/
#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

struct HeavyObject {
    char name[200];
    HeavyObject() { name[0] = '\0', cout << "ctor\n"; }
    HeavyObject(const HeavyObject &) { cout << "Copy\n"; }
    HeavyObject(HeavyObject &&) noexcept { cout << "Move\n"; }
    HeavyObject & operator = (const HeavyObject &) {
        cout << "C-assign\n";
        return *this;
    }
    HeavyObject & operator = (HeavyObject &&) noexcept {
        cout << "M-assign\n";
        return *this;    
    }
    ~HeavyObject() { cout << "dtor\n"; }
};

HeavyObject func() {
    HeavyObject ans;
    for(int i = 0 ; i < 1 ; ++i)
        strcat(ans.name,"Hastin");
    return std::move(ans);
}

// HeavyObject globe;

signed main() {
    HeavyObject tmp = func();
    tmp = func();
    cout << tmp.name << '\n';
    return 0;
}