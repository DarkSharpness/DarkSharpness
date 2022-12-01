#include <bits/stdc++.h>

class LinkList {
    //TODO
};

class LinkListArray {
private:
    int len;
    LinkList **lists;

public:
    LinkListArray(int n): len(n) {
        lists = new LinkList*[n];
        for (int i = 0; i < n; ++i) lists[i] = new LinkList;
    }
    ~LinkListArray() {
        for (int i = 0; i < len; ++i) {
            delete lists[i];
        }
        delete []lists;
    }

    void insertNumber(int n, int x) {
        lists[n]->push(x);
    }
    int queryNumber(int n, int k) {
        return lists[n]->getKth(k);
    }
    void mergeLists(int p, int q) {
        lists[p]->merge(lists[q]);
    }
};

int main() {
    int len, m;
    scanf("%d%d", &len, &m);
    LinkListArray a = LinkListArray(len);
    for (int i = 0, op, s1, s2; i < m; ++i) {
        scanf("%d%d%d", &op, &s1, &s2);
        if (op == 0) {
            a.insertNumber(s1, s2);
        }
        if (op == 1) {
            printf("%d\n", a.queryNumber(s1, s2));
        }
        if (op == 2) {
            a.mergeLists(s1, s2);
        }
    }
    return 0;
}