#include <vector>
using namespace std;
typedef long long ll;

typedef size_t value;
//template <typename value>
class Matrix{
    private:
        size_t len,wid;
        struct array2D{
            vector <value> v;
            value * operator [](const size_t &_X)
            {
                return &v[_X];
            }
            array2D()
            {
                v.clear();   
            }
        }vec;
    
    public:
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
    }
};



int main()
{
   

    return 0;
}