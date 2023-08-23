#include <iostream>
#include <cstring>
using namespace std;


signed main() {
    char name[100 + 1]; // 注意，有一位留给 '\0'
    cin >> name;
    int len = strlen(name);
    for(int i = len - 1 ; i >= 0 ; --i)
        cout << name[i];
    return 0;
}
