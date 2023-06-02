#include <iostream>
#include <cstring>
using namespace std;

const int N = 1024;
char str[N];
char sub[N];

int main() {
    cin >> str >> sub;
    int n = strlen(str);
    int m = strlen(sub);
    int ans = 0;
    for(int i = 0 ; i + m <= n ; ++i)
        if(strncmp(sub,str + i,m) == 0)
            ++ans;
    cout << ans;
    return 0;
}