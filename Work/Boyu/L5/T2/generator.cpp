#include <bits/stdc++.h>
using namespace std;

signed __std(int n) {
    int y = n / 10; // 第一行
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

    y = n % 10;
    if(y == 0) {
        cout << "*****\n";
    } else if(y == 1) {
        cout << "--*--\n";
    } else if(y == 2) {
        cout << "-****\n";
    } else if(y == 3) {
        cout << "*****\n";
    } else if(y == 4) {
        cout << "--**-\n";
    } else if(y == 5) {
        cout << "*****\n";
    } else if(y == 6) {
        cout << "-****\n";
    } else if(y == 7) {
        cout << "*****\n";
    } else if(y == 8){
        cout << "*****\n";
    } else {
        cout << "*****\n";
    }

    y = n / 10; // 第二行
    if(y > 0) {
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

    y = n % 10;
    if(y == 0) {
        cout << "*---*\n";
    } else if(y == 1) {
        cout << "***--\n";
    } else if(y == 2) {
        cout << "*---*\n";
    } else if(y == 3) {
        cout << "----*\n";
    } else if(y == 4) {
        cout << "-*-*-\n";
    } else if(y == 5) {
        cout << "*----\n";
    } else if(y == 6) {
        cout << "*----\n";
    } else if(y == 7) {
        cout << "---**\n";
    } else if(y == 8){
        cout << "*---*\n";
    } else {
        cout << "*---*\n";
    }

    y = n / 10; // 第三行
    if(y > 0) {
        if(y == 1) {
            cout << "--*-- ";
        } else if(y == 2) {
            cout << "---*- ";
        } else if(y == 3) {
            cout << "***** ";
        } else if(y == 4) {
            cout << "*--*- ";
        } else if(y == 5) {
            cout << "***** ";
        } else if(y == 6) {
            cout << "***** ";
        } else if(y == 7) {
            cout << "--**- ";
        } else if(y == 8){
            cout << "***** ";
        } else {
            cout << "***** ";
        }
    }

    y = n % 10;
    if(y == 0) {
        cout << "*---*\n";
    } else if(y == 1) {
        cout << "--*--\n";
    } else if(y == 2) {
        cout << "---*-\n";
    } else if(y == 3) {
        cout << "*****\n";
    } else if(y == 4) {
        cout << "*--*-\n";
    } else if(y == 5) {
        cout << "*****\n";
    } else if(y == 6) {
        cout << "*****\n";
    } else if(y == 7) {
        cout << "--**-\n";
    } else if(y == 8){
        cout << "*****\n";
    } else {
        cout << "*****\n";
    }

    y = n / 10; // 第四行
    if(y > 0) {
        if(y == 1) {
            cout << "--*-- ";
        } else if(y == 2) {
            cout << "-**-- ";
        } else if(y == 3) {
            cout << "----* ";
        } else if(y == 4) {
            cout << "***** ";
        } else if(y == 5) {
            cout << "---** ";
        } else if(y == 6) {
            cout << "*---* ";
        } else if(y == 7) {
            cout << "-**-- ";
        } else if(y == 8){
            cout << "*---* ";
        } else {
            cout << "---** ";
        }
    }

    y = n % 10;
    if(y == 0) {
        cout << "*---*\n";
    } else if(y == 1) {
        cout << "--*--\n";
    } else if(y == 2) {
        cout << "-**--\n";
    } else if(y == 3) {
        cout << "----*\n";
    } else if(y == 4) {
        cout << "*****\n";
    } else if(y == 5) {
        cout << "---**\n";
    } else if(y == 6) {
        cout << "*---*\n";
    } else if(y == 7) {
        cout << "-**--\n";
    } else if(y == 8){
        cout << "*---*\n";
    } else {
        cout << "---**\n";
    }

    y = n / 10;
    if(y > 0) {
        if(y == 1) {
            cout << "***** ";
        } else if(y == 2) {
            cout << "***** ";
        } else if(y == 3) {
            cout << "***** ";
        } else if(y == 4) {
            cout << "---*- ";
        } else if(y == 5) {
            cout << "****- ";
        } else if(y == 6) {
            cout << "***** ";
        } else if(y == 7) {
            cout << "**--- ";
        } else if(y == 8){
            cout << "***** ";
        } else {
            cout << "****- ";
        }
    }

    y = n % 10;
    if(y == 0) {
        cout << "*****";
    } else if(y == 1) {
        cout << "*****";
    } else if(y == 2) {
        cout << "*****";
    } else if(y == 3) {
        cout << "*****";
    } else if(y == 4) {
        cout << "---*-";
    } else if(y == 5) {
        cout << "****-";
    } else if(y == 6) {
        cout << "*****";
    } else if(y == 7) {
        cout << "**---";
    } else if(y == 8){
        cout << "*****";
    } else {
        cout << "****-";
    }
    return 0;
}


signed main() {
    for(int i = 1 ; i <= 100 ; ++i) {
        string in = to_string(i) + ".in";
        string out = to_string(i) + ".out";

        freopen(in.c_str(),"w",stdout);
        cout << i - 1;
        freopen(out.c_str(),"w",stdout);
        __std(i - 1);
    }
    return 0;
}