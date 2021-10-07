#include <bits/allocator.h>
#include <bits/stdc++.h>
#ifndef _Dark_STL_H_
#define _Dark_STL_H_

namespace std{

typedef size_t value;

//template <typename value>
class Vector{
    private: 
    allocator <value> V;
    value * ptr;
    size_t siz;  
    size_t capa;  
    public:
    void push_back(const value& _val)
    {
        
    }

};


}


using namespace std;
typedef long long ll;
const int _GCCSB=sizeof(Vector);

int main()
{
    return 0;
}

#endif