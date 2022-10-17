#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 16;
const ll M = 1e18;
//location of '$' , total = top // loc[i+1] - loc[i] = size[i]
int loc[N],top = 0; 

char m[N],s[N];

int lenm = 0,lens = 0;

#define size(X) (loc[X+1]-loc[X]-1) // the size of X-th substr
#define sub(_X) (s+loc[_X]+1)       // the _X-th substr beginning  

void readm() {
    static uint8_t ch;
    ch = getchar();
    while(ch <= 32 || ch >= 127) ch = getchar();
    while(33 <= ch && ch <= 126) {
        m[lenm++] = ch;
        ch = getchar();
    }
}
void reads() {
    static uint8_t ch;
    ch = getchar();
    loc[0] = -1;
    while(ch <= 32 || ch >= 127) ch = getchar();
    while(33 <= ch && ch <= 126) {
        if(ch == '$') {
            loc[++top] = lens;
        }
        s[lens++] = ch;
        ch = getchar();
    }
    loc[top+1] = lens;
}

//print s in [l,r)
void print(const char * cptr,int l,int r) {
    for(int i = l ; i < r ; ++i) 
        putchar(cptr[i]);
}

int dep = 0;    //maximum depth
ll maxr = 0;   //maximum right position
int k,q;
const int maxK = 64;// 1ULL << 63 > 1e18
ll len[maxK];      //The length after x iteration.  
ll l[N],r[N];      //l r query

/*
    idx[k][n]   = the n-th string index  
*/
ll idx[maxK][N];



//search the answer for [l,r)
void dfs(int depth,ll l,ll r) {//r < len[depth]
    if(l == r) {return ;}// end
    if(depth == 0) { // end,down to m
        print(m,l,r);
        return;
    }
    ll * index = idx[depth]; //the current index array
    int locL = upper_bound(index,index+top+1,l) 
               - index - 1;
        //index[locL] <= l , index[locL+1] > l
    int locR = upper_bound(index,index+top+1,r-1) 
               - index - 1;
        //index[locR] <=  r-1 , index[locR+1] > r-1
    l -= index[locL]; //relative index
    r -= index[locR]; //relative index
    if(locL != locR) {
        if(l < size(locL)) {
            print(sub(locL),l,size(locL));
            dfs(depth-1,0,len[depth-1]);
        } else {
            dfs(depth-1,l-size(locL),len[depth-1]);
        }


        for(int i = locL + 1 ; i != locR ; ++i) {
            print(sub(i),0,size(i));
            dfs(depth-1,0,len[depth-1]);
        }


        if(r > size(locR)) {
            print(sub(locR),0,size(locR));
            dfs(depth-1,0,r-size(locR));
        } else {
            print(sub(locR),0,r);
        }
    } else {// locL == locR
        if(l < size(locL) && r < size(locL)) {
            print(sub(locL),l,r);
        } else if(l >= size(locL) && r >= size(locL)) {
            dfs(depth-1,l-size(locL),r-size(locL));
        } else {
            print(sub(locL),l,size(locL));
            dfs(depth-1,0,r-size(locL));
        }

    }
    
}


void getMaxDepth() { // calculate dep
    dep = 0;        
    len[0] = lenm;
    __int128_t last = lenm;
    while(last <= maxr && dep != k) {
        len[dep] = last;
        last *= top;
        last += lens - top;
        ++dep;
    }//len[dep] > maxr && unused
}
void getIdx() {//calculate Idx
    for(ll i = 1 ; i <= dep ; ++i) {
        ll *index = idx[i];
        index[0] = 0;
        for(int j = 0 ; j < top ; ++j) {
            if(index[j] > maxr) // to prevent overflow
                index[j+1] = index[j] + 2;
            else // no overflow possibility
                index[j+1] = index[j] + size(j) + len[i-1];
        }
        //index[j] : start index of the j-th block in depth i
    }
}

//k != 1
void work() {
    getMaxDepth();
    getIdx();
    ll bias = (k-dep) * loc[1];   //loc[1] == size(0);
    for(ll i = 0 ; i < q ; ++i) { //First handle the case over dep.
        if(r[i] <= bias) { // l[i] < bias
            for(int j = l[i] ; j < r[i] ; ++j) {
                putchar(s[j % loc[1]]);
            }
        } else {
            if(l[i] < bias) { // r[i] > bias;
                for(int j = l[i] ; j < bias ; ++j) {
                    putchar(s[j % loc[1]]);
                }
                l[i] = bias;
            }
            dfs(dep,l[i]-bias,r[i]-bias);
        }
        puts("");//end of a line
    }
}

void work1() {
    ll bias = loc[1] * k;
    for(int i = 0 ; i < q ; ++i) {
        if(r[i] <= bias) {
            for(ll j = l[i] ; j < r[i] ; ++j) {
                putchar(s[j % loc[1]]);
            }
        } else { // r[i] > bias
            if(l[i] < bias) {// print out before bias
                for(ll j = l[i] ; j < bias ; ++j) {
                    putchar(s[j % loc[1]]);
                }
                l[i] = bias;
            }
            l[i] -= bias;
            r[i] -= bias;
            if(l[i] >= lenm) { // r[i] > lenm
                for(ll j = l[i]-lenm ; j < r[i]-lenm ; ++j) {
                    putchar(s[loc[1] + 1 + j % size(1)]);
                }
            } else if(r[i] <= lenm) { // l[i] < lenm
                print(m,l[i],r[i]);
            } else { // l[i] < lenm , r[i] > lenm
                print(m,l[i],lenm);
                for(ll j = 0 ; j < r[i]-lenm ; ++j) {
                    putchar(s[loc[1] + 1 + j % size(1)]);
                }
            }

        }
        puts("");
    }
}

int main() {
    readm();
    reads();
    scanf("%d%d",&k,&q);
    for(int i = 0 ; i < q; ++i) {
        scanf("%llu%llu",l + i,r + i);
        --l[i];
        if(r[i]  > maxr) maxr = r[i];
    }
    if(top == 1) work1();
    else work();
    return 0;
}