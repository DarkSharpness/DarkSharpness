#include <iostream>
#include <vector>
using namespace std;


signed main() {
    char buf[16];
    int n,m;
    vector <int> st; // Stack 1
    vector <int> re; // Stack 2
    scanf("%d",&n);
    while(n--) {
        scanf("%s",buf);
        switch (buf[1]) {
            case 'u':
                scanf("%d",&m);
                st.push_back(m);
                break;
            case 'o':
                re.push_back(st.back());
                st.pop_back();
                break;
            case 'e':
                st.push_back(re.back());
                re.pop_back();
                break;
            case 'r':
                printf("%d\n",st.back());
                break;
        }
    }
    return 0;
}