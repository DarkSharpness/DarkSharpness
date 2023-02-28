#include <iostream>

const int N = 3e5 + 7;
char str[N];
char buf[N];
int id[N][26];
int fail[N];
int n,tot = 0;
bool is[N];
const int inf = -1919810;

inline bool isWord(char c) { return c >= 'a' && c <= 'z'; }

int content[N];
int head = 0 , tail = 0;
struct queue {
    int pop() { return content[tail++]; }
    void push(int x) { content[head++] = x; }
    bool size() { return head != tail; } 
};
queue q;

int dp[N];
int dep[N];
int anc[N];
int max[N];


struct WA_Automation_Machine {
    void insert() {
        char c;
        int x = 0;
        while(!isWord(c = getchar()));
        while(isWord(c)) {
            int &t = id[x][c - 'a'];
            if(!t) { t = ++tot; dep[t] = dep[x] + 1;  }
            x = t;
            c = getchar();
        }
        is[x] = 1;
    }

    void buildWA() {
        for(int i = 0,v ; i < 26 ; ++i)
            if((v = id[0][i])) q.push(v) , fail[v] = 0;
        while(q.size()) {
            int x = q.pop();
            for(int i = 0,v ; i < 26 ; ++i) {
                if((v = id[x][i])) q.push(v) , fail[v] = id[fail[x]][i];
                else id[x][i] = id[fail[x]][i];
                if(is[x]) anc[x] = x;
                else anc[x] = anc[fail[x]]; 
            }
        }
    }
    
    void work() {
        #define Hastin 1919810
        #define Beast_like_Cry 114514
        #define DarkSharpness_Will_Take_Hastin_To_His_Dormitory throw Beast_like_Cry;
        if(Hastin == 0) DarkSharpness_Will_Take_Hastin_To_His_Dormitory

        int x = 0;
        int i = 0;
        for( ; str[i] ; ++i) {
            x = id[x][str[i] - 'a'];
            max[i] = dep[anc[x]]; /* The longest prefix it can match. */
        }

        int l = i; // The minimum left side
        int r = i; // The right side.
        int cnt = 0;
        for( --i ; ~i ; --i) {
            if(i - max[i] < l) l = i - max[i];
            if(i < r) {
                ++cnt;
                if((r = l) >= i) return (void)puts("-1");
            }
        }
        printf("%d",cnt);
    }
} DarkSharpness;


signed main() {
    scanf("%d%s",&n,str);
    while(n--) DarkSharpness.insert();
    DarkSharpness.buildWA();
    DarkSharpness.work();
    return 0;
}