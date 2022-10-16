#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 256;
const int mp[10] = {
    0,1,1,2,2,2,2,3,3,4
};
const int tail[8] = {
    1,1,3,1,9,9,7,9
};
int cnt_2,cnt_5;
int tail_odd = 1;
const int mpp[4] = {
    6,2,4,8
};
const char ans[10] = {
    '1','1','2','6','4',
    '2','2','4','2','8'
};
const int tail_mp[100] = {
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9
};


void getOdd(int x) {
    int r,q;
    while(1) {
        if(x < 10) {
            tail_odd *= tail[mp[x] & 7];
            if(tail_odd > 10) 
                tail_odd = tail_mp[tail_odd];
            cnt_5 += (x >= 5);
            break;
        }
        q = x / 10;
        r = x - q * 10;
        tail_odd *= tail[((q<<2) + mp[r]) & 7];
        if(tail_odd > 10) 
            tail_odd = tail_mp[tail_odd];
        cnt_5 += q + (r >= 5);
        x /= 5;
    }
}

void getEven(int x) {
    x >>= 1;
    while(x) {
        getOdd(x);
        cnt_2 += x;
        x >>= 1;
    }
}



int main() {
    int n;
    scanf("%d",&n);
    if(n < 10) {
        putchar(ans[n]);
        return 0;
    }
    getOdd(n);
    getEven(n);
    cnt_2 -= cnt_5;
    cnt_2 &= 3;
    putchar(tail_mp[mpp[cnt_2] * tail_odd] ^ '0');
    return 0;
}