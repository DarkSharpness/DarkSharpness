#include "utils.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "Game.h"
int getDigit(const int num, const int digitPos) {
    static int div[] = {10000,1000,100,10,1};
    return (num / div[digitPos]) % 10;
    // It takes about 1 line of code.
}
bool isValidNum(int num) {
    bool vis[10];
    memset(vis,0,sizeof(vis));
    for(int i = 0 ; i < 4 ; ++i) {
        if(vis[num % 10]) {
            return false;
        }
        vis[num % 10] = true;
        num /= 10; 
    }
    return true;
    // It takes about 13 lines of code.
}
bool isValidResult(const Result res) {
    return res.A >= 0 &&
           res.B >= 0 && 
           res.A + res.B <= 4; 
    // It takes about 8 lines of code.
}
void printNum(const int num) {
    for(int i = 0 ; i < 4 ; ++i) {
        printf("%d",getDigit(num,i));
    }
    // It takes about 3 lines of code.
}
void printWithWidth(const char s[], const int width) {
    printf("%s",s);
    int len = strlen(s);
    if(len < width) for(int i = len ; i < width ; ++i) putchar(' ');
    // It takes about 4 lines of code.
}
