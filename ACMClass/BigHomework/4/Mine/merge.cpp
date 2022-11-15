/*
    代码合并器
    注意你的.h.cc等文件
    需要有末尾空行
    不然会报错
    这是一个良好的代码规范
*/

#include<bits/stdc++.h>
using namespace std;
//#define int lont long


signed main() {
    freopen("BigInteger/number.h","r",stdin);
    freopen("submit.cpp","w",stdout);
    string str;
    while(getline(cin,str)) {
        cout << str << '\n';
    }
    freopen("BigInteger/number.cc","r",stdin);
    cin.clear();
    while(getline(cin,str)) {
        if(str != "#include \"number.h\"") {
            cout << str << '\n';
        }
    }
    return 0;
}
