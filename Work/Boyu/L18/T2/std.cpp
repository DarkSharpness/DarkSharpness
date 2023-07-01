#include <iostream>
#include <algorithm>
using namespace std;

std::string str[100];

int main() {
    int n;
    cin >> n;
    for(int i = 0 ; i != n ; ++i) cin >> str[i];
    std::sort(str,str + n,[](const std::string &lhs,const std::string rhs) {
        if(lhs.size() != rhs.size()) return lhs.size() < rhs.size();
        return lhs < rhs;
    });
    for(int i = 0 ; i != n ; ++i) cout << str[i] << '\n';
    return 0;
}