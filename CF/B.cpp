#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
    ios::sync_with_stdio(false);
    int T;
    #define endl '\n'
    cin >> T;
    int n;
    while(T--) {
        cin >> n ;
        for(int i = 1 ; i <=n ; ++i) {
            cout << '1' << ' ';
            for(int j = 2 ;  j < i ; ++j) {
                cout << '0' << ' ';
            }
            if(i != 1) cout << '1' ;
            cout << endl;
        }
    }


    return 0;
}
