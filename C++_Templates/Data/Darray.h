#ifndef _DARRAY_H_
#define _DARRAY_H_
#include <vector>
namespace std{
typedef size_t value ;
const size_t dim=2;
//template <typename value,size_t dim>
//template <size_t dim>
class Darray{
    private:
    vector <value> v;
    public:
    inline value & operator[](const size_t &_X)
    {
        return v[_X];
    }
    
    Darray  ()
    {
    }

};
}



#endif
