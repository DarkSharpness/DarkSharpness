#include<algorithm>

void Init(int **&p,int n){//初始化，n为vector的个数,传入的p指向nullptr
    using int_ptr = int *;
    p = new int_ptr[n+1];
    p[0] = new int[n+1];
    for(int i = 1 ; i <= n ; ++i) {
        p[i] = new int[17];// initialized by 17 in size
        p[i][0] = 0;// size
        p[0][i] = 16;// capacity
    }
}
void Add_element(int **&p,int x,int y){
    int *ptr = p[x];
    if(*ptr == (*p)[x]) {
        int * t = new int[((*ptr)<<1)|1];
        for(int i = 0 ; i <= (*ptr) ; ++i) 
            t[i] = ptr[i];
        delete [] ptr;
        ptr = p[x] = t;
        (*p)[x] <<= 1;// expand capa
    }
    // now size < capa
    ptr[++(*ptr)] = y;
}
int Get_element(int **&p,int x,int k){
    return p[x][k];
}
void Clear(int **&p,int n){
    for(int i = 0 ; i <= n ; ++i)
        delete [] p[i];
    delete [] p;
    p = nullptr;
}