#include <iostream>

const int N = 1003;



signed main() {
    std::string str;
    std::cin >> str;
    int n = str.size();
    for(int i = n - 1 ; i > 0 ; --i)
        if(str.substr(0,i) == str.substr(n - i,i)) {
            std::cout << str.substr(0,i);
            return 0;
        }
    std::cout << 0;
    return 0;
}
