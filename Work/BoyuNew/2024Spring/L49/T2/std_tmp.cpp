#include <iostream>
using namespace std;

struct node {
    int     data;
    node *  next;
};

const int N = 5005;
node tmp[N];

signed main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1 ; i < n ; ++i) {
        tmp[i].data = i;
        tmp[i].next = tmp + i + 1;
    }

    tmp[n].data = n;
    tmp[n].next = tmp + 1;

    node *pre = nullptr;
    node *nxt = tmp + 1; 

    while (pre != nxt) {
        for (int i = 0 ; i < m - 1 ; ++i) {
            pre = nxt;
            nxt = nxt->next;
        }

        // nxt dead.
        cout << nxt->data << " ";
        pre->next = nxt->next;

        pre = nxt;
        nxt = pre->next;
    }
    return 0;
}
