#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const double Temp[] = // Targeted temperatures
{ 32.50,41.00,48.00,54.80,62.00,69.40,80.5,89.90,101.50 };

const double K  = -0.00268;
const double B  = 3851;
const double Ug = 1.289;
const double T0 = 273.15; 

signed main() {
    freopen("NTC1.txt","w",stdout);
    for(auto x : Temp) {
        double T = x + T0;
        dark::printline(T,'\t',-B / (T * T));
    }
    freopen("PN1.txt","w",stdout);
    for(auto x : Temp) {
        double T = x + T0;
        dark::printline(T,'\t',K / (Ug + K * T));
    }
    return 0;
}