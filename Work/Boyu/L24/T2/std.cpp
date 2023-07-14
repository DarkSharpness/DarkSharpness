#include <iostream>


signed main() {
    std::string word,text;
    std::cin >> word >> text;
    while (true) {
        unsigned long long index = text.find(word);
        if(index == text.npos) break;
        text.replace(index,word.length(),"");
    }
    if(text.length())
        std::cout << text;
    else
        std::cout << 0;
    return 0;
}