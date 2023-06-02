#include <iostream>
#include <cstring>
using namespace std;
const int N = 1024;
char str[N];
/* 不要抄题解,不要用这种写法,OI 用不到的! */

signed main() {
    scanf("%s",str);
    char *__f = str; /* Front   */
    char *__c = str; /* Current */
    while(*__c != 0) { /* Not end. */
        if(!isdigit(*__c)) *__f++ = *__c++;
        else {
            while(isdigit(*__c)) putchar(*__c++);
            putchar('\n');
        }
    }
    *__f = 0;
    puts(str);
    return 0;
}
