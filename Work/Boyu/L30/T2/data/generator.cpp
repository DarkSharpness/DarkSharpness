#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        freopen(in.c_str(),"w",stdout);
        const int M = i * i * i * 100 - 50;
        int stk_size = 0;
        int mem_size = 0;
        printf("%d\n",M + 1);
        int x = 0;
        for(int i = 0 ; i < M ; ++i) {
            if(x == 3)  x = rand() % 3;
            else        x = rand() % 999 % 4;
            if(!stk_size && (x & 1)) --x;
            if(!mem_size &&  x == 2) x = 0;
            switch(x) {
                case 0:
                    printf("push %d\n",i);
                    ++stk_size;
                    break;
                case 1:
                    printf("pop\n");
                    --stk_size;
                    ++mem_size;
                    break;
                case 2:
                    printf("revoke\n");
                    --mem_size;
                    ++stk_size;
                    break;
                case 3:
                    printf("print\n");
                    break;
                default: throw;
            }
        }
        if(stk_size == 0) throw;
        printf("print\n");
        freopen(out.c_str(),"w",stdout);
        freopen(in.c_str(),"r",stdin);
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
    }
    return 0;
}