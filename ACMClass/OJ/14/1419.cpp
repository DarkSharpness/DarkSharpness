#include <bits/stdc++.h>
// #include <Dark/inout>

/* Read function part. */

namespace dark {

/* Read a visible char. (Using standard ASCII.) */
char &read_char(char &ch) {
    do { ch = getchar(); } while(ch > 126 || ch < 33);
    return ch;
}

/* Read a signed integer. */
template <class integer>
integer &read_s(integer &num) {
    char ch;
    bool flag = false;
    num = 0;
    while(!isdigit(ch = getchar())) if(ch == '-') flag = true;
    while(isdigit(ch)) {
        num = num * 10 + (ch ^ '0');
        ch  = getchar();
    }
    if(flag) num = -num;
    return num;
}

/* Read an unsigned integer. */
template <class integer>
integer &read_u(integer &num) {
    char ch;
    num = 0;
    while(!isdigit(ch = getchar()));
    while(isdigit(ch)) {
        num = num * 10 + (ch ^ '0');
        ch  = getchar();
    }
    return num;
}

/* Special case : read a visible char. */
auto &read(char &ch) { return read_char(ch); }

auto &read(signed char  &num)  { return read_s(num); }
auto &read(signed short &num)  { return read_s(num); }
auto &read(signed int   &num)  { return read_s(num); }
auto &read(signed long  &num)  { return read_s(num); }

auto &read(unsigned char  &num) { return read_u(num); }
auto &read(unsigned short &num) { return read_u(num); }
auto &read(unsigned int   &num) { return read_u(num); }
auto &read(unsigned long  &num) { return read_u(num); }

auto &read(signed   long long &num) { return read_s(num); }
auto &read(unsigned long long &num) { return read_u(num); }

#ifdef __SIZEOF_INT128__ /* Special support for int128. */
auto &read(__int128_t &num)  { return read_s(num); }
auto &read(__uint128_t &num) { return read_u(num); }
#endif

auto &read(float &num)  { scanf("%f",&num) ; return num; }
auto &read(double &num) { scanf("%lf",&num); return num; }

#ifdef __SIZEOF_LONG_DOUBLE__
auto &read(long double &num) { scanf("%Lf",&num); return num; }
#endif

/* Read a visible string. (Using standard ASCII.) */
char *read(char *str) { 
    do { *str   = getchar(); } while(*str > 126 || *str < 33); 
    do { *++str = getchar(); } while(*str > 32 && *str < 127);
    *str = '\0';
    return str;
}


/* Read in a sequence of integers. */
template <class integer,class ...integers>
void read_s(integer &arg,integers &...args) { read_s(arg); read_s(args...); }
/* Read in a sequence of integers. */
template <class integer,class ...integers>
void read_u(integer &arg,integers &...args) { read_u(arg); read_u(args...); }
/* Read in a sequence of integers. */
template <class integer,class ...integers>
void read(integer &arg,integers &...args)   { read(arg);   read(args...); }



/* Paramless version. */


/* Read an integer any given type. */
template <class integer>
integer read() { integer tmp; return read(tmp); }
/* Read an unsigned integer of given type. */
template <class integer>
integer read_u() { integer tmp; return read_u(tmp); }
/* Read a signed integer of given type. */
template <class integer>
integer read_s() { integer tmp; return read_s(tmp); }
/* Read a visible char. */
char read_char() { char tmp; return read_char(tmp); }

/* Avoid misusage. */
template <class integer>
void read(integer &arg) = delete;

}


const int N = 1003;
int n,m;

char g[N][N];
int  v[N][N][2];

struct node {
    int x,y;
    bool state;
    node() = default;
    node(int a,int b,bool c) { x = a , y = b, state = c; }
};

std::queue <node> q;

const int dir[2][4] = {
    { 1,0,-1,0 },
    { 0,1,0,-1 }
};

bool check(int x,int y,bool z) {
    if(x < 0 || y < 0 || x >= n || y >= m) return false;
    if(v[x][y][z] || g[x][y] == '1') return false;
    return true;
}


void bfs() {
    while(!q.empty()) {
        auto [x,y,z] = q.front();
        q.pop();
        for(int i = 0 ; i < 4 ; ++i) {
            int tx = x + dir[0][i];
            int ty = y + dir[1][i];
            if(!check(tx,ty,z)) continue;

            v[tx][ty][z] = v[x][y][z] + 1;
            q.emplace(tx,ty,z);

            if(z && g[tx][ty] == '3') {
                // printf("%d %d\n",tx,ty);
                printf("%d",v[tx][ty][z]);
                break;
            }

            if(!z && g[tx][ty] == '4' && !v[tx][ty][1]) {
                v[tx][ty][1] = v[x][y][0] + 1;
                q.emplace(tx,ty,1);
            }
        }
    }
}

signed main() {
    dark::read_u(m,n);
    for(int i = 0 ; i < n ; ++i)
        for(int j = 0 ; j < m ; ++j) 
            if(dark::read_char(g[i][j]) == '2')
                q.emplace(i,j,0);
    bfs();
    return 0;
}