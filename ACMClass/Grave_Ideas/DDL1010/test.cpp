#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

float a[8] = {
    0.00000000000001036,
    0.000000000001030, 
    0.00000000010252, 
    0.0000000102022, 
    0.00000101512574,
    0.00010100585584,
    0.010050016708,
    1.0
};


int main() {
    for(int i = 0 ; i < 50 ; ++i) {
        cout << a[7] - exp(0.01*i) << "\n";
        for(int j = 7 ; j ; --j)
            a[j] += a[j-1];
    }

    return 0;
}