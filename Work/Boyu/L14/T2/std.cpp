/* 说了不要抄袭标程!!! */
#include <iostream>
using namespace std;

const int N = 1001;
int a[N];

int search(int l,int r,int q) {
    int mid = (l + r) / 2;
    if(a[mid] == q) return mid;
    if(a[mid] > q)  return search(l,mid - 1,q);
    else            return search(mid + 1,r,q);
}

int main() {
    int n,q;
    cin >> n;
    for(int i = 1 ; i <= n ; ++i) cin >> a[i];
    cin >> q;
    cout << search(1,n,q);
    return 0;
}