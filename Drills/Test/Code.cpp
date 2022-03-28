#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef size_t ull;
struct node{
    node *a;
    node *b;
    int y;
    //int &x=y;
};
const int t=sizeof(node);
typedef node * nodeptr;
char *c="abc";
char *d="def";
nodeptr emptynode[3]={(nodeptr)c,(nodeptr)d,NULL};


int main()
{
    int* A=(int*)emptynode;
    for(int i=0 ; i<=5; ++i)
        cout << A[i]<<endl;
    return 0;
}