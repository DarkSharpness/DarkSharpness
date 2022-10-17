#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a,ll b) {
    if(b == 0) return a;
    return gcd(b,a%b);
}

using value_type = ll;

struct fraction {
    value_type num;
    value_type den;
    
    fraction operator+(const fraction &B) const{
        return fraction(num * B.den + B.num * den,
                        den * B.den);
    }
    fraction operator-(const fraction &B) const{ 
        return fraction(num * B.den - B.num * den,
                        den * B.den);
    }
    fraction operator*(const fraction &B) const{
        return fraction(num * B.num,
                        den * B.den);
    }
    fraction operator /(const fraction &B) const{
        return fraction(num * B.den,
                        den * B.num);
    }
    bool operator ==(const fraction &B) const{
        return num * B.den == den * B.num;
    }
    bool operator !=(const fraction &B) const{
        return num * B.den != den * B.num;
    }
    void print() const{
        value_type N = num;
        value_type D = den;
        char ch[20];
        int tot = 0;
        int top = 12;
        if(D != 1) {
            while(D) {
                ch[++tot] = (D % 10) ^ '0';
                --top;
                D /= 10;
            }
            ch[++tot] = '/';
            --top;
        }
        if(N < 0) putchar('-'),--top,N = -N;
        if(N == 0) --top,putchar('0');
        while(N) {
            ch[++tot] = (N % 10) ^ '0';
            N /= 10;
            --top;
        }
        while(tot) putchar(ch[tot--]);
        while(--top) putchar(' ');
    }
    fraction() {
        num = 0;
        den = 1;
    }
    fraction(const value_type &B) {
        num = B;
        den = 1;
    }
    explicit fraction(value_type A,value_type B) {
        if(A == 0) {
            num = 0;
            den = 1;
        }
        else {
            bool flag = false;
            if(A < 0) {
                flag ^= true;
                A = -A;
            }
            if(B < 0) {
                flag ^= true;
                B = -B;
            }
            value_type G = gcd(A,B);
            num = A/G;
            den = B/G;
            if(flag) num *= -1;
        }
    }

};

fraction a[100][100];
fraction b[100][100];
int n;
void print() {
    bool flag = false;
    for(int i = 1 ; i <= n ; ++i) {
        for(int j = 1; j <= 2*n ; ++j)
            if(a[i][j] != b[i][j]) {flag = true;break;}
        if(flag) break;
    }
    if(!flag) return;

    for(int i = 1 ; i <= n ; ++i) {
        for(int j = 1 ; j <= 2*n ; ++j) {
            a[i][j].print();
            b[i][j] = a[i][j];
        }
        puts("");
    }
    puts("END");
}

void Gauss()
{
    for (int i=1;i<=n;i++)
    {
        if (a[i][i]==0)
        {
            for (int j=i+1;j<=n;j++)
                if (a[j][i]!=0)
                {
                    for (int k=i;k<=2*n;k++) swap(a[i][k],a[j][k]);
                    print();
                    break;
                }
        }
        for (int j=i+1;j<=n;j++)
        {
            fraction tmp=a[j][i]/a[i][i];
            if(tmp == 0) continue;
            for (int k=i;k<=2*n;k++) a[j][k]=a[j][k]-a[i][k]*tmp;
            
        }
        print();
    }
    for (int i=n;i;i--)
    {
        for (int j=i-1;j;j--)
        {
            fraction tmp=a[j][i]/a[i][i];
            for (int k=i;k<=2*n;k++) a[j][k]=a[j][k]-a[i][k]*tmp;
        }
        print();
    }
    for (int i=1;i<=n;i++)
    {
        fraction tmp=a[i][i];
        for (int j=i;j<=2*n;j++) a[i][j]=a[i][j]/tmp;
    }
    print();
}

int main() {
    cin >> n;
    for(int i = 1 ; i <= n ; ++i) {
        for(int j = 1 ; j <= n ; ++j) {
            int x;
            cin >> x;
            a[i][j] = x;
        }
        for(int j = n+1 ; j <= n << 1 ; ++j) {
            a[i][j] = (j-n) == i; 
        }
    }
    //print();
    Gauss();
    system("pause");
    return 0;
}