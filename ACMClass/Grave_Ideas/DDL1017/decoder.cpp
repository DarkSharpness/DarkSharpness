#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector <string> command;
long long v[100];
long long l[10];
long long e[10]; 

inline ll read(const char *& str) {
    char ch = *str;
    bool flag = false;
    while(!isdigit(ch)) {
        if(ch == '-') flag = true;
        ch = *(++str);
    }
    ll tmp = 0;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^ '0');
        ch = *(++str);
    }
    if(flag) tmp *= -1;
    return tmp;
}

bool check_empty(const string &str) {
    for(char ch : str) 
        if(ch != '\0' && ch !='\n' && ch != ' ') return false;
    return true;
}

int top = 0;
void work() {
    int cnt = 0;
    bool load = false;
    bool overflow = false;
    bool TLE = false;
    char mode;
    for(uint32_t i = 0 ; i < command.size() ; ++i) {
        if(check_empty(command[i])) continue;//empty line
        ++cnt;
        if(cnt >= 1e4) {
            TLE = true;
        }
        const string & str = command[i];
        const char * ptr = str.c_str(); 
        ++ptr;
        switch(str[0]) {
            case 'N' :{
                ll k = read(ptr);
                ll n = read(ptr);
                v[k] = n;
                break;
            }
            case 'L' : {
                ll k = read(ptr);
                if(!load) {
                    load = true;
                    l[1] = v[k];
                } else {
                    overflow = false; //reset runup lever
                    load = false;
                    l[2] = v[k];
                    if(mode == '+') {
                        e[1] = l[1] + l[2];
                    } else if(mode == '-') {
                        e[1] = l[1] - l[2];
                        if(e[1] < 0) overflow = true;
                    } else {
                        //cnt += 59;
                        if(mode == '*') {
                            e[1] = l[1] * l[2];
                        } else {
                            if(l[2] == 0) overflow = true;
                            else {
                                e[1] = l[1] % l[2];
                                e[2] = l[1] / l[2];
                            }
                        } 
                    }
                }
                break;
            }
            case 'S': {
                ll k = read(ptr);
                if(str[1] == '\'') {
                    v[k] = e[2];
                } else {
                    v[k] = e[1];
                }
                break;
            }
            case 'P': {
                ll k = read(ptr);
                printf("%lld\n",v[k]);
                break;
            }
            case 'B': {
                --cnt;
                ll k = read(ptr);
                i -= k;
                cnt += k;
                break;
            }
            case 'F': {
                --cnt;
                ll k = read(ptr);
                i += k;
                cnt += k;
                break;
            }
            case '?': {
                --cnt;
                if(!overflow) break;
                ll k = read(ptr);
                cnt += k;
                if(str[1] == 'B') i -= k;
                else i += k;
                break; 
            }
            default: // signal 
                mode = str[0];     
        }

    }
    printf("time:%d\n",cnt);
    if(TLE) {
        printf("Time Limit Exceed!");
        return ;
    }
}

int main() {
//    cin >> v[0];
    string str;
    cout << "请输入文件相对路径与名称(样例:1.txt):" << endl;
    cin >> str;
    freopen(str.c_str(),"r",stdin);
    while(true) {
        getline(cin,str);
        //cout << str << endl;
        if(str == "end") break;
        command.push_back(str);
    }
    work();
    return 0;
}