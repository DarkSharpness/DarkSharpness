#include <bits/stdc++.h>
// #include <Dark/inout>
// #define int long long
// using ll = long long;
// using ull = unsigned long long;
using namespace std;


signed main() {
    int n;
    cin >> n;
    if(n == 0) {
        cout << "*****\n"
             << "*---*\n"
             << "*---*\n"
             << "*---*\n"
             << "*****\n";
    } else {
        int y = n % 10;
        if(y > 0) {
            if(y == 1) {
                cout << "--*-- ";
            } else if(y == 2) {
                cout << "-**** ";
            } else if(y == 3) {
                cout << "***** ";
            } else if(y == 4) {
                cout << "--**- ";
            } else if(y == 5) {
                cout << "***** ";
            } else if(y == 6) {
                cout << "-**** ";
            } else if(y == 7) {
                cout << "***** ";
            } else if(y == 8){
                cout << "***** ";
            } else {
                cout << "***** ";
            }
        }

        if(y > 0) {
            y = n % 10;
            if(y == 1) {
                cout << "***-- ";
            } else if(y == 2) {
                cout << "*---* ";
            } else if(y == 3) {
                cout << "----* ";
            } else if(y == 4) {
                cout << "-*-*- ";
            } else if(y == 5) {
                cout << "*---- ";
            } else if(y == 6) {
                cout << "*---- ";
            } else if(y == 7) {
                cout << "---** ";
            } else if(y == 8){
                cout << "*---* ";
            } else {
                cout << "*---* ";
            }
        }

        if(y > 0) {
            y = n % 10;
            if(y == 1) {
                cout << "--*-- ";
            } else if(y == 2) {
                cout << "---*- ";
            } else if(y == 3) {
                cout << "***** ";
            } else if(y == 4) {
                cout << "*--*- ";
            } else if(y == 5) {
                cout << "*---- ";
            } else if(y == 6) {
                cout << "*---- ";
            } else if(y == 7) {
                cout << "---** ";
            } else if(y == 8){
                cout << "*---* ";
            } else {
                cout << "*---* ";
            }
        }

        if(y > 0) {
            y = n % 10;
            if(y == 1) {
                cout << "***-- ";
            } else if(y == 2) {
                cout << "*---* ";
            } else if(y == 3) {
                cout << "----* ";
            } else if(y == 4) {
                cout << "-*-*- ";
            } else if(y == 5) {
                cout << "*---- ";
            } else if(y == 6) {
                cout << "*---- ";
            } else if(y == 7) {
                cout << "---** ";
            } else if(y == 8){
                cout << "*---* ";
            } else {
                cout << "*---* ";
            }
        }

        if(y > 0) {
            y = n % 10;
            if(y == 1) {
                cout << "***-- ";
            } else if(y == 2) {
                cout << "*---* ";
            } else if(y == 3) {
                cout << "----* ";
            } else if(y == 4) {
                cout << "-*-*- ";
            } else if(y == 5) {
                cout << "*---- ";
            } else if(y == 6) {
                cout << "*---- ";
            } else if(y == 7) {
                cout << "---** ";
            } else if(y == 8){
                cout << "*---* ";
            } else {
                cout << "*---* ";
            }
        }


    }


    return 0;
}