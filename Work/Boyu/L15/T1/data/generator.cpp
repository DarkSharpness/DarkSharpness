#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int N = 1022;

char char_map(int i) {
    static bool last = false;
    i %= (26 + 26 + 10);
    if(last && rand() % 4) i += 52; 
    if(i < 26) {
        last = false;
        return 'a' + i;
    }
    i -= 26;
    if(i < 26) {
        last = false;
        return 'A' + i;
    }
    if(last == false) {
        last = true;
        return '1' + i % 9;
    } else {
        return '0' + i % 10;   
    }
}


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        string str;
        int len = rand() % (N / 100 * i * i);  
        while(len--) str.push_back(char_map(rand()));
        freopen( in.data(),"w",stdout);
        dark::writeline(str.data());
        freopen(out.data(),"w",stdout);
        char *__f = str.data(); /* Front   */
        char *__c = str.data(); /* Current */
        while(*__c != 0) { /* Not end. */
            if(!isdigit(*__c)) *__f++ = *__c++;
            else {
                while(isdigit(*__c)) putchar(*__c++);
                putchar('\n');
            }
        }
        *__f = 0;
        puts(str.data());
    }
    return 0;
}