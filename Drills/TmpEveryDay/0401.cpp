#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


int a,b,c;


inline int check(int x){
    a=x%10;
    x=x/10;
    b=x%10;
    x=x/10;
    c=x;
    if(a==b||b==c||a==c) return 0;
    if(x%3==0&&((a & b& c&1)==1)) return 2;
    return 1;

}
int ans,num;


int main()
{
    for(int i=100 ; i<=999 ; ++i){
        switch(check(i)){
            case 2:
                ans++;
            case 1:
                num++;
        }
    }
    cout << ans << " "<<num<<endl;
    return 0;
}