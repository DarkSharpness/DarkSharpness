#include <stdio.h>
#include <string.h>

void sortstr(char str[]) {
    int  loc[12];
    int  num[12];
    int  cnt = 0;
    int len = strlen(str);
    for(int i = 0 ; i < len ; ++i) {
        loc[cnt] = i;
        num[cnt] = cnt;
        ++cnt;
        while(str[i] != ' ' && i != len) ++i;
        str[i] = '\0';
    }
    loc[cnt] = len + 1;
    for(int i = 0 ; i < cnt ; ++i) {
        for(int j = i + 1 ; j < cnt; ++j) {
            if(loc[num[i]+1] - loc[num[i]] < loc[num[j]+1] - loc[num[j]]) continue;
            int flag = 0;
            if(loc[num[i]+1] - loc[num[i]] == loc[num[j]+1] - loc[num[j]]) {
                if(strcmp(str + loc[num[i]],str + loc[num[j]]) > 0) flag = 1;
            } else {
                flag = 1;
            }
            if(flag == 1) { // swap the value of num[i] and num[j]
                num[i] ^= num[j];
                num[j] ^= num[i];
                num[i] ^= num[j];
            }
        }
    }
    char ans[256];
    int idx = 0;
    for(int i = 0 ; i < cnt ; ++i) {
        idx = strcpy(ans+idx,str + loc[num[i]]) - ans;
        idx += loc[num[i] + 1] - loc[num[i]];
        if(idx < len) ans[idx - 1] = ' ';
    }
    strcpy(str,ans);
}


int main() {
    char str[256];
    scanf("%[^\n]*c",str);
    sortstr(str);
    printf("%s\n",str);
    return 0;
}