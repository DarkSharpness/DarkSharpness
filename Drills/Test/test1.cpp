#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct node{
    array <size_t,26> _A;
    size_t id;
    size_t &operator [](const size_t &_X){
        return _A[_X];
    }
    size_t  operator [](const size_t &_X)const{
        return _A[_X];
    }
    node()
    {
        _A.fill(0);
        id=0;
    }

}x;

int main()
{
    cin >> x[1];
    cout << x[1]<< endl;
    return 0;
}