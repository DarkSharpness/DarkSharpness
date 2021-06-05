//#include<bits/stdc++.h>
#include <math.h>
#ifndef _Dark_Math_H_
#define _Dark_Math_H_

namespace std{

typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;



template <typename A,typename B>
A quickpow(A _base,B _up)
{
    A ans=1;
    for(;_up;_up>>=1)
    {
        if(_up&1) ans*=_base;
        _base=_base*_base;
    }
    return ans;
}


 
}
#endif