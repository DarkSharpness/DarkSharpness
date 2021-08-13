#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector < int > vec;

int main()
{
    int n;
    while(scanf("%d",&n)&&n) vec.push_back(n);
    
    int * c=&vec[0];
    cout << c[0] <<endl;
    c++;
    cout << c[0] <<endl;
    return 0;
}