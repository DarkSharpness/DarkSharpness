#include <vector>
#include <iostream>
using namespace std;
typedef long long ll;

typedef double value;
//template <typename value>
class Matrix{

private:    
    vector <value> v;
    size_t row,col;//row column
    bool trans;    //transpose of a matrix
    //A specific value pointer
    struct valueptr{
        private: 
        value * ptr;
        size_t base;
        public:
       
        //Array-like reference.
        value& operator [](const size_t &_X){
            return *(ptr+_X*base);
        }
        //Array-like reference.
        value  operator [](const size_t &_X)const{
            return *(ptr+_X*base);
        }
        //Pointer-like reference
        value& operator *(void){
            return *ptr;
        }
        //Pointer-like reference
        value& operator *(void)const{
            return *ptr;
        }
        //Pointer-like addition.
        valueptr operator +(const size_t &_X){
            return valueptr(ptr+_X*base,base);
        }
        //Initialization
        valueptr (value *_X,size_t _B){
            ptr=_X,
            base=_B;
        }
        //Initialization
        valueptr (const value *_X,const size_t _B){
            ptr=const_cast<value *>(_X);
            base=_B;
        }
        
    };
public:

    valueptr operator [](const size_t &_X) {
        return  trans ?   valueptr(&v[_X],row) : valueptr(&v[_X*col],1) ;
    }
    const valueptr operator [](const size_t &_X) const{
        return  trans ?   valueptr(&v[_X],row) : valueptr(&v[_X*col],1) ;
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
    cout <<"Row:"<<_M.Row()<<" Col:"<<_M.Col()<<endl;
    for(size_t i=0 ; i<_M.Row() ; ++i)
    {
        for(size_t j=0 ; j<_M.Col() ; ++j) 
            cout << _M[i][j] << " ";
    }
    puts("");
}

inline void readM(Matrix &_M)
{
    size_t x,y;
    puts("输入行数列数");
    cin >>x >> y;
    _M.set(x,y);
    puts("输入矩阵");
    for(size_t i=0 ; i<_M.Row() ; ++i)
    {
        for(size_t j=0 ; j<_M.Col() ; ++j) 
            cin >>  _M[i][j] ;
    }
}


Matrix M(3,3),T(3,3);
vector <Matrix> m;

int main()
{ 
    puts("简单矩阵工具");
    puts("输入0或非数字 退出");
    puts("输入1/2 输入矩阵 A/B");
    puts("输入3/4 转置矩阵 A/B");
    puts("输入5/6 输出矩阵 A/B");
    puts("输入7/8 输出A+B A-B");
    puts("输入其他数字 输出A*B (无法乘会返回A)");
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
    
    
    string command;
    while(cin >> command )
    {
        
    }


    system("pause");
    return 0;
}