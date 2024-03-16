#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;


signed main() {
    char ch[10] = "abcdefg";
    dark::writeline(ch);

    dark::writeline("read:",dark::read_char());

    auto tmp = dark::read_u <int> ();
    dark::writeline(tmp);
    return 0;
}
