#include <bits/stdc++.h>

class LinkList {
  private:
    struct node {
        node *nxt;
        int value;
    };
    node head;
  public:
    LinkList() {
        head.nxt = &head;
        head.value = 2147483647; 
    }
    ~LinkList() {
        node *now = head.nxt;
        while(now != &head) {
            node *tmp = now;
            now = now->nxt;
            delete tmp; 
        }
        head.nxt = &head;
    }
    void push(int value) {
        node *now = &head;
        node *nxt = head.nxt;
        while(nxt->value < value) {
            now = nxt;
            nxt = nxt->nxt;
        }
        now->nxt = new node {nxt,value};
    }
    int getKth(int kth) const{
        const node *now = head.nxt;
        while(now != &head && kth--) now = now->nxt;
        if(now == &head) return -1;
        else             return now->value;
    }
    void merge(LinkList *L) {
        // LinkList *ans;
        node *ptr1 = &head;
        node *nxt1 = head.nxt;
        node *ptr2 = L->head.nxt;
        while(nxt1 != &head && ptr2 != &L->head) {
            if(nxt1->value >= ptr2->value) {                
                node *tmp = ptr2->nxt;
                ptr2->nxt = ptr1->nxt;
                ptr1->nxt = ptr2;
                ptr2 = tmp;
            }
            ptr1 = nxt1;
            nxt1 = nxt1->nxt;
        }
        if(ptr2 == &L->head) {ptr2->nxt = ptr2;}
        else {
            ptr1->nxt = ptr2;
            nxt1 = ptr2->nxt;
            while(nxt1 != &L->head) {
                ptr2 = nxt1;
                nxt1 = nxt1->nxt;
            }
            ptr2->nxt = &head;
            nxt1->nxt = nxt1;
        }
    }
    void print() const{
        node *ptr = head.nxt;
        while(ptr != &head) {
            printf("%d ",ptr->value);
            ptr = ptr->nxt;
        }
    }
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
    void print() const{
        for(int i = 0 ; i < len ; ++i) {
            printf("%d:",i);
            lists[i]->print();
            putchar('\n');
        }
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
        // printf("PRINT:\n");
        // a.print();
    }
    return 0;
}