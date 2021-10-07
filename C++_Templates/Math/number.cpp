#pragma GCC optimize(3)
#include<bits/stdc++.h>
namespace std{

class number{
typedef unsigned int U; //Define U as unsigned int
    bool signal;
    vector <U> v;

public:
    number()
    {

    }
    ~number()
    {

    }

    //Boolean operators.Written in the class.

    //Normal '!'
    inline bool operator!(void)const{
        return (v.size()==1&&v.front()==0u);
    }
    
};

}



using namespace std;




int main()
{

    return 0;
}