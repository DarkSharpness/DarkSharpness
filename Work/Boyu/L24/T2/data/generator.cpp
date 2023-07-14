#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

string generate(int n) {
    string str;
    str.resize(n);
    while(n--) { str[n] = rand() % 26 + 'a'; }
    return str;
}

signed main() {
    srand(time(NULL));
    for(int i = 4 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const size_t n = (1 << i);
        auto word = generate((rand() % (n >> 2)) | 1);
        auto text = generate((rand() % (n >> 2)) | 1) + word;
        text.reserve(n);
        while(text.length() < n) {
            if(text.length() + word.length() <= n) {
                if((rand() & 0b111) == 0b010) {
                    text += word;
                    continue;
                }
            } text.push_back(rand() % 26 + 'a');
        }
        freopen(in.data(),"w",stdout);
        std::cout << word << ' ' << text;
        freopen(out.data(),"w",stdout);
        while (true) {
            unsigned long long index = text.find(word);
            if(index == text.npos) break;
            text.replace(index,word.length(),"");
        }
        if(text.length())
            std::cout << text;
        else
            std::cout << 0;
    }
    return 0;
}