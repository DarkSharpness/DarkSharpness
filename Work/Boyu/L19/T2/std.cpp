#include <iostream>
using namespace std;

const int N = 32;

enum tmp {
    add,
    beq,
    bne,
    blt,
    bge,
    jal,
    jr,
    li,
    lw,
    mv,
    out,
    put,
    sll,
    sra,
    sub,
    sw,
    End
};

int reg[N]; /*  */
struct command {
    tmp type;
    int x,y,z;
} cmd[N];

int main() {
    int n,m,c;
    cin >> n >> m >> c;
    std::string buffer;
    for(int i = 1 ; i <= n ; ++i) {
        tmp type;
        int x,y,z;
        cin >> buffer;
        if     (buffer == "add") type = add,cin >> x >> y >> z;
        else if(buffer == "beq") type = beq,cin >> x >> y >> z;
        else if(buffer == "bne") type = bne,cin >> x >> y >> z;
        else if(buffer == "blt") type = blt,cin >> x >> y >> z;
        else if(buffer == "bge") type = bge,cin >> x >> y >> z;
        else if(buffer == "jal") type = jal,cin >> x >> y;
        else if(buffer == "jr" ) type = jr ,cin >> x;
        else if(buffer == "li" ) type = li ,cin >> x >> y;
        else if(buffer == "lw" ) type = lw ,cin >> x >> y;
        else if(buffer == "mv" ) type = mv ,cin >> x >> y;
        else if(buffer == "out") type = out,cin >> x >> y;
        else if(buffer == "put") type = put,cin >> x >> y;
        else if(buffer == "sll") type = sll,cin >> x >> y >> z;
        else if(buffer == "sra") type = sra,cin >> x >> y >> z;
        else if(buffer == "sub") type = sub,cin >> x >> y >> z;
        else if(buffer == "sw")  type = sw ,cin >> x >> y;
        else type = End;
        cmd[i] = {type,x,y,z};
    }
    int pc = 1;
    while(m--) {
        if(pc < 1 || pc > n) {
            cout << "Runtime Error!";
            return 0;
        }
        int next = pc + 1;
        int x = cmd[pc].x;
        int y = cmd[pc].y;
        int z = cmd[pc].z;
        switch(cmd[pc].type) {
            case add: reg[x] = reg[y] + reg[z]; break;
            case beq: if(reg[x] == reg[y]) next = z; break;
            case bne: if(reg[x] != reg[y]) next = z; break;
            case blt: if(reg[x] <  reg[y]) next = z; break;
            case bge: if(reg[x] >= reg[y]) next = z; break;
            case jal: reg[x] = next;       next = y; break;
            case jr : next = reg[x];        break;
            case li : reg[x] = y;           break;
            case lw : reg[x] = reg[reg[y]]; break;
            case mv : reg[x] = reg[y];      break;
            case out: cout <<  (int)(reg[x] + y); break;
            case put: cout << (char)(reg[x] + y); break;
            case sll: reg[x] = reg[y] << reg[z];  break;
            case sra: reg[x] = reg[y] >> reg[z];  break;
            case sub: reg[x] = reg[y] - reg[z]; break;
            case sw : reg[reg[x]] = reg[y];     break;
            default: /* End case. */
                cout << "Exit with code 0.";
                return 0;
        }
        pc = next;
        reg[0] = 0;
    } cout << "Time Limit Exceed!";
    return 0;
}