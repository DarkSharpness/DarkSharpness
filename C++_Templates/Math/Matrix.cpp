#include <vector>
#include <iostream>
using namespace std;
typedef long long ll;

typedef size_t value;
//template <typename value>
class Matrix{

private:
    size_t len,wid;
    vector <value> v;
public:
    value * operator [](const size_t &_X)
    {
        return &v[_X*len];
    }
    //Initial with nothing
    Matrix()
    {   
        len=0;
        wid=0;
    }
    //Initial with give length and width
    Matrix(const size_t &_len,const size_t &_wid)
    {
        len=_len;
        wid=_wid;
        v.resize(_len*_wid);
    }
    value A()
    {
        if(!len||!wid) return ;
        if(len!=wid) return v[0];
        return ;    
    }
};



Matrix M(3,3);


int main()
{
    for(int i=0 ; i<3 ; ++i)
        for(int j=0 ; j<3 ; ++j) 
            cin>>M[i][j];

    return 0;
}