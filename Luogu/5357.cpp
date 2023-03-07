#include <bits/stdc++.h>
// #include <Dark/inout>

/* Write a integer and start a new line.*/
template <class integer>
void writeline(integer num) {
    if(!num) return (void) puts("0");
    if(num < 0) num = -num,putchar('-');
    static char ch[3 * sizeof(integer) + 1] = {0};
    int top = 3 * sizeof(integer) - 1;
    while(num) {
        ch[--top] = '0' ^ (num % 10);
        num /= 10;
    }
    puts(ch + top);
}

const int N = 2e2 + 3;

struct edge { int nxt,to; } e[N];
int head[N],ecc;
inline void adde(int fr,int to) 
{ e[++ecc] = (edge) {head[fr],to}; head[fr] = ecc; }

int id[N][26];
int fail[N];
int rev[N];
int sum[N];

inline bool is_char(char ch) { return ch >= 'a' && ch <= 'z'; }

int qq[N],h,t;
struct queue {
    void push(int x) noexcept { qq[++t] = x; }
    int pop() noexcept   { return qq[++h]; }
    bool size() noexcept { return h != t; }
};

void dfs(int u) {
    for(int i = head[u] ; i ; i = e[i].nxt) {
        dfs(e[i].to);
        sum[u] += sum[e[i].to];
    }
}

struct WA_machine {
    int cnt;
    void insert(const int i) noexcept {
        char ch;
        int x = 0;
        while(!is_char(ch = getchar()));
        while(is_char(ch)) {
            int &dir = id[x][ch - 'a'];
            x = (dir ? dir : dir = ++cnt);
            ch = getchar();
        }
        rev[i] = x;
    }

    void build() noexcept {
        queue q;
        for(int i = 0 ; i < 26 ; ++i)
            if(id[0][i])
                fail[id[0][i]] = 0,
                q.push(id[0][i]);

        while(q.size()) {
            int x = q.pop();
            for(int i = 0 ; i < 26 ; ++i) {
                if(id[x][i]) 
                    fail[id[x][i]] = id[fail[x]][i],
                    q.push(id[x][i]);
                else id[x][i] = id[fail[x]][i];
            }
        }
    }

    void work() noexcept {
        char ch;
        int x = 0;
        while(!is_char(ch = getchar()));
        while(is_char(ch)) {
            ++sum[x = id[x][ch - 'a']];
            ch = getchar();
        }
        for(int i = 1 ; i <= cnt ; ++i) adde(fail[i],i);
        
        dfs(0);
    }

    WA_machine() noexcept : cnt(0) {}
} conless;


signed main() {
    int n;
    scanf("%d",&n);

    for(int i = 0 ; i < n ; ++i) conless.insert(i);

    conless.build();
    conless.work();

    for(int i = 0 ; i < n ; ++i) writeline(sum[rev[i]]);
    return 0;
}