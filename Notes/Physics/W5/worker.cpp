#include <cmath>
#include <Dark/inout>

const double Temp[10] = // Targeted temperatures
{ 0.00,32.50,41.00,48.00,54.80,62.00,69.40,80.5,89.90,101.50 };
double ntc[10];   // sum of available ntc data
double pn[10];    // sum of available pn  data
size_t count[10]; // count of available   data
const double Delta = 0.005;
const double T_0   = 273.15;

signed main() {
    freopen("data_m.txt","r",stdin); // input file
    int id;     // useless
    double T;   // Temperature
    double ch0, // useless
           ch1, // NTC
           ch2, // PN
           ch3; // useless
    while(dark::read(T) > 1) { // Special token marking the end
        dark::read(id,ch0,ch1,ch2,ch3);   // Read params from data_m.txt
        for(int i = 1 ; i <= 9 ; ++i)
            if(fabs(T - Temp[i]) < Delta) { // Temperature range
                ++count[i];
                ntc[i] += ch1;
                pn[i]  += ch2;
            }
    }
    freopen("NTC.txt","w",stdout); // output NTC data
    for(int i = 1 ; i <= 9 ; ++i) {
        dark::write(1 / (Temp[i] + T_0));
        dark::write('\t');
        dark::writeline(log(ntc[i] / count[i]));
    }
    freopen("PN.txt","w",stdout); // output PN data
    for(int i = 1 ; i <= 9 ; ++i) {
        dark::write(T_0 + Temp[i]);
        dark::write('\t');
        dark::writeline(pn[i] / count[i]);
    }
    return 0;
}
