#include <vector>
#include <iostream>
using namespace std;
typedef long long ll;

typedef double value;
//template <typename value>
class Matrix{

private:
    size_t row,col;//row column
    vector <value> v;
    bool trans;    //transpose of a matrix
    struct valueptr{
        private: 
        value * ptr;
        size_t base;
        public:
        value& operator [](const size_t &_X){
            return *(ptr+_X*base);
        }
        value  operator[](const size_t &_X)const{
            return *(ptr+_X*base);
        }
        value    operator *(void){
            return *ptr;
        }
        valueptr operator +(const size_t &_X){
            return valueptr(ptr+_X*base,base);
        }
        valueptr (value *_X,size_t _B){
            ptr=_X,base=_B;
        }
        valueptr (const value *_X,const size_t _B){
            ptr=const_cast<value *>(_X),base=_B;
        }
        
    };
public:
    
    valueptr operator [](const size_t &_X) {
        return  trans ?   valueptr(&v[_X],row) : valueptr(&v[_X*row],1) ;
    }
    const valueptr operator [](const size_t &_X) const{
        return  trans ?   valueptr(&v[_X],row) : valueptr(&v[_X*row],1) ;
    }
    value at(const size_t &_loc)
    {
        return v[_loc];
    }
    //Return the only element.(If not , return the first element)
    explicit operator value()
    {
        if(col==0||row==0){value x;return x;}
        return v[0];
    }
    Matrix operator +(Matrix _X)const
    {
        if(_X.col!=col||_X.row!=row) return *this;
        if(trans==_X.trans)
            for(size_t i=0 ; i<col*row ; ++i)
                    _X.v[i]+=v[i];
        else
            for(size_t i=0 ; i<row; ++i)
                for(size_t j=0 ; j<col; ++j)
                    _X[i][j]+=(*this)[i][j];
        
        return _X;

    }
    Matrix operator -(Matrix _X)const
    {
        if(_X.col!=col||_X.row!=row) return *this;
        if(trans==_X.trans)
            for(size_t i=0 ; i<col*row ; ++i)
                    _X.v[i]=v[i]-_X.v[i];
        else
            for(size_t i=0 ; i<row; ++i)
                for(size_t j=0 ; j<col; ++j)
                    _X[i][j]=(*this)[i][j]-_X[i][j];
        
        return _X;

    }
   
    Matrix operator *(const Matrix &_X)
    {
        cout << col << " " << _X.row << endl;
        if(col!=_X.row) return *this;
        if(col==0||row==0||_X.col==0) return *this;
        Matrix _T(row,_X.col);
        for(size_t i=0 ; i<row ;++i)
            for(size_t j=0 ; j<_X.col ;++j)   
                for(size_t k=0; k<col;++k)
                    _T[i][j]+=(*this)[i][k]*_X[k][j];
        return _T;
    }
    //Initial with nothing
    Matrix()
    {   
        col=0;
        row=0;
        trans=false;
    }
    //Initial with given length and width
    Matrix(const size_t &_row,const size_t &_col)
    {
        row=_row;
        col=_col;
        v.resize(_row*_col);
        trans=false;
    }
    
    void transpose()
    {
        trans = ! trans;
        swap(col,row);
    } 
    void transpose(const bool &_X)
    {
        trans = _X;
    } 
    size_t Row()const{return row;}
    size_t Col()const{return col;}
    void set(const size_t &_row,const size_t &_col)
    {
        row=_row;
        col=_col;
        v.resize(_row*_col);
    }
};

inline void printM(const Matrix &_M)
{
    
    for(size_t i=0 ; i<_M.Row() ; ++i)
    {
        for(size_t j=0 ; j<_M.Col() ; ++j) 
            cout << _M[i][j] << " ";
        puts("T");
    }
    puts("");
}

inline void readM(Matrix &_M)
{
    size_t x,y;
    puts("????????????");
    cin >>x >> y;
    _M.set(x,y);
    puts("????????");
    for(size_t i=0 ; i<_M.Row() ; ++i)
    {
        for(size_t j=0 ; j<_M.Col() ; ++j) 
            cin >>  _M[i][j] ;
    }
}


Matrix M(3,3),T(3,3);


int main()
{ 
    puts("????????????");
    puts("????0???????? ????");
    puts("????1/2 ???????? A/B");
    puts("????3/4 ???????? A/B");
    puts("????5/6 ???????? A/B");
    puts("????7/8 ????A+B A-B");
    puts("???????????? ????A*B (????????????A)");
    int x;
    while(cin >>x && x)
    {
        switch(x)
        {
            #define bk break
            case 1: readM(M);bk;
            case 2: readM(T);bk;
            case 3: M.transpose();bk;
            case 4: T.transpose();bk;
            case 5: printM(M);bk;
            case 6: printM(T);bk;
            case 7: printM(M+T);bk;
            case 8: printM(M-T);bk;
            default:printM(M*T);
        }
    }
    system("pause");
    return 0;
}