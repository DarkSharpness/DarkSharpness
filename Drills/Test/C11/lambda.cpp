#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
// [captures] <tparams> {params} lambda-specifiers{body}
// []  capture nothing(no global/contextual variables)
// [=] capture variables by value
// [&] capture variables by reference
// [=,&a,&b...] except a,b... use value
// [&,a,b]      except a,b... use reference
// [a,&b] specificly decide
// [this] use this pointer in member function

// similar to the operator() of a class



int main()
{   
    int x=1,y=2;
    auto plusfunc =[=](int a,int b) -> int{ return x+y ;};
    auto cmp= [](const int &a,const int &b)->bool{return a>b;};
    priority_queue<int>;
    return 0;
}