#include <iostream>
using namespace std;
typedef long long ll;
const ll N = 1e6 + 10;
const ll M = 1e6 + 10;
char s[M];
int mem[N];
struct queue {
    int head = 0;
    int tail = 0;
    inline void push(int x) noexcept { mem[tail++] = x; }
    inline int pop() noexcept { return mem[head++]; }
    inline bool size() noexcept { return head != tail; }
};


int id[N][26],nxt[N] , cnt=0;
bool match[N];
struct ACAutomation{
    void insert(char *c,int num) {
        int j = 0;
        for(int i = 0 ; c[i] ; ++i)  {
            int x = c[i] - 'a';
            if(!id[j][x]) id[j][x] = ++cnt; 
            j = id[j][x];
        }
        match[j] = 1;
    }
    void buildnxt() {
        queue q;
        for(int i = 0 ; i < 26 ; ++i) if(id[0][i]) nxt[id[0][i]] = 0 , q.push(id[0][i]);
        while(q.size()) {
            int v = q.pop();
            for(int i = 0 ; i != 26 ; ++i ) {
                if(id[v][i]) nxt[id[v][i]] = id[nxt[v]][i] , q.push(id[v][i]);
                else id[v][i] = id[nxt[v]][i];
            }
        }
    }
    void query(char *c) {
        int j = 0;
        for(int i = 0 ; c[i] ;++i) {
            j = id[j][c[i] - 'a'];
            if(match[j]) return (void)puts("valar morghulis");
        }
        puts("valar dohaeris");
    }
} AC;

int main() {
    int n;
    scanf("%d",&n);
    for(int i = 1 ; i <= n ; ++i) 
        scanf("%s",s) , AC.insert(s,i);
    AC.buildnxt();
    scanf("%s",s);
    AC.query(s);
    return 0;
}