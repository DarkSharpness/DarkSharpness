/*
    ����ϲ���
    ע�����.h.cc���ļ�
    ��Ҫ��ĩβ����
    ��Ȼ�ᱨ��
    ����һ�����õĴ���淶
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
