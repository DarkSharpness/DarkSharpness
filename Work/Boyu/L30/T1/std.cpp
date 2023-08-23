#include <iostream>
#include <vector>
#include <cstring>

const int N = 1e6 + 2;
char buf[N];
int  nxt[N];

bool test(int len) {
    std::vector <int> v;
    for(int i = 0 ; i < len ; ++i) {
        if(buf[i] == '(') {
            v.push_back(i);
        } else if(buf[i] == ')') {
            if(v.empty()) {
                return false;
            }
            nxt[v.back()] = i;
            v.pop_back();
        }
    }
    return v.empty();
}

signed main() {
    scanf("%s", buf);
    int len = strlen(buf);
    if(test(len)) {
        for(int i = 0 ; i < len ; ++i)
            if(buf[i] == '(') printf("%d ", nxt[i]);
    } else {
        puts("No");
    }

    return 0;
}