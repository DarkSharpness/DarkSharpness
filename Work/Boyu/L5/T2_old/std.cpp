#include <iostream>
using namespace std;


signed main() {
    int n;
    cin >> n;
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
