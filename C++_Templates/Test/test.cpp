#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const char * c="123";


int main()
{
    int l=strlen(c);
    printf("%d",l);
    for(int i=0 ; i<=l ; ++i)
        printf("%c %d\n",c[i],(int(c[i])));

    return 0;
}