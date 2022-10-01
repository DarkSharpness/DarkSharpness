#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1024;
struct biter{
    typedef unsigned long long ull;
    ull data[N];
    ull n;
    inline void set(int loc) {
        data[loc>>6] |=  1ull << (loc & 63); 
    }

    inline void set(int loc,bool val) {
        if(val) set(loc);
        else  reset(loc); 
    }  
    inline void reset(int loc) {
        data[loc>>6] &=  ~(1ull << (loc & 63)); 
    }
    inline void reset() {
        memset(data,0,n<<3);
    }
    inline void set() {
        memset(data,127,n<<3);
    }
    inline bool test(int loc) {
        return  data[loc>>6] & 1ull << (loc & 63);
    }
    inline void filp(int loc) {
        data[loc>>6] ^= 1ull << (loc & 63);
    }
    biter operator <<=(int length) {
        ull tmp = 0;
        int ret = length >> 6;
        if(ret >= n) {
            reset();
            return ;
        }
        length &= 63;// length % 64
        memset(data,0,ret << 3);
        for(int j = n-ret-1,i = n-1; j ; --i,--j) {
            data[i] = data[j]
        }
    }
    inline void init(ull number) {
        n = number;
    }
};



int main() {
    bitset<N> b;
    b <<= 1;   
    size_t n;
    cin >> n;
    return 0;
}
