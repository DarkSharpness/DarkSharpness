#include "Dark/inout"
#include "Dark/string"

using namespace dark;


signed main() {
    // int x;
    char str[20];
    iput >> str;
    auto it = string_view(str);
    for(auto c : it) {
        oput << c;
    }


    return 0;
}