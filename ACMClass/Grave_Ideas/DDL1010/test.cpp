#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

float a[8] = {
    0.00000000000001,
    0.00000000000103, 
    0.00000000010252, 
    0.00000001020220, 
    0.00000101512574,
    0.00010100585584,
    0.01005001670800,
    1.00000000000000
};


int main() {
    for(int i = 0 ; i < 50 ; ++i) {
        cout << a[7] - exp(0.01*i) << "\n";
        for(int j = 7 ; j ; --j)
            a[j] += a[j-1];
    }

    return 0;
}