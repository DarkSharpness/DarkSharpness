#include <algorithm>
#include <iostream>
#include <format>

std::string H[20];
std::string B[20];

int main() {
    freopen("input.txt","r",stdin);
    for(int i = 0 ; i < 20 ; ++i)
        std::cin >> H[i] >> B[i];
    freopen("output.txt","w",stdout);
    std::reverse(H, H + 5);
    std::reverse(B, B + 5);
    std::reverse(H + 10, H + 15);
    std::reverse(B + 10, B + 15);
    for(int i = 0 ; i < 20 ; ++i)
        std::cout << H[i] << '\t' << B[i] << '\n';
    return 0;
}