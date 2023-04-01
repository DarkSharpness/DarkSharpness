#include<bits/stdc++.h>
const int N = 4e5 + 3;
int n,m,maxn,len;
const double PI = std::acos(-1.0);
int rev[N << 1];

struct complex {
    double real,imag;
    complex(double _real = 0,double _imag= 0) {
        real = _real;
        imag = _imag;
    }

    complex operator =(const complex& _A) {
        real = _A.real;
        imag =_A.imag;
        return *this;
    }
    complex operator +(const complex& _A) const{
        return complex (_A.real+real,_A.imag+imag);
    }
    complex operator -(const complex& _A) const{
        return complex (real-_A.real,imag-_A.imag);
    }
    complex operator *(const complex& _A) const{
        return complex(_A.real*real-_A.imag*imag,
                       _A.real*imag+_A.imag*real);
    }
    complex operator *=(const complex& _A) {
        double temp = real;
        real = real*_A.real - imag*_A.imag;
        imag = imag*_A.real + temp*_A.imag;
        return *this;
    }
    void set(double sita) {
        real = std::cos(sita);
        imag = std::sin(sita);
        //return *this;
    }
};

complex a[N << 1];

void FFT(complex* A ,int length,int flag = 1){
    for(int i = 0 ; i < length; ++i)
        if(i < rev[i]) std::swap(A[i],A[rev[i]]);
    complex w;
    complex x,y;
    complex temp;
    for(int i = 1; i < length; i<<=1) {
        w.set((PI/i)*flag);
        for(int j = 0; j < length; j+=(i<<1)) {
            //temp.real=1.0 , temp.imag=0.0;
            temp.real = 1.0;
            temp.imag = 0.0;
            for(int k = 0; k < i;++k ,temp *= w) {
                x = A[j+k] , y = A[j+k+i] * temp;
                A[j+k]   = x + y;
                A[j+k+i] = x - y;
            }
        }
    }
}

void IFFT(complex* A,int length) { FFT(A,length,-1); }

inline int round_near(const double X) { return int(X+0.5); }

/* Write a integer. */
template <class integer>
void writeInt(integer num) {
    if(!num) return (void) putchar('0');
    if(num < 0) num = -num , putchar('-');
    static char ch[3 * sizeof(integer)];
    int top = 0;
    while(num) {
        ch[top++] = '0' ^ (num % 10);
        num /= 10;
    }
    while(top--) putchar(ch[top]);
}


int main() {
    scanf("%d%d",&n,&m);
    for(int i = 0; i <= n ; ++i) scanf("%lf",&a[i].real);
    for(int i = 0; i <= m ; ++i) scanf("%lf",&a[i].imag);
    maxn = 1;
    len  = 0;
    while(maxn <= n+m) maxn <<= 1,len++;
    for(int i = 0;i < maxn;i++)
        rev[i]= ( rev[i >> 1] >> 1 )| ( (i&1) << (len - 1) ) ;// 1 << len+1 = maxn
    FFT(a,maxn);
    for(int i = 0 ; i <=maxn; ++i) 
        a[i] = a[i] * a[i];    
    IFFT(a,maxn);
    for(int i = 0 ; i <= n + m ; ++i) 
        writeInt(round_near(a[i].imag / (maxn << 1)) ) , putchar(' ');
    return 0;
}
