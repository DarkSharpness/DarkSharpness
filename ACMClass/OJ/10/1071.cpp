#include <bits/stdc++.h>

class LinkList {
    struct node {
        int val;
        node *nxt;
        node(int v = 1919810 << 10,node *ptr = nullptr) :val(v),nxt(ptr) {}
    };
    node *head;
  public:
    LinkList() {
        head = new node;
        head->nxt = head;
    }
    ~LinkList() {
        node *cur = head->nxt;
        while(cur != head) {
            node *tmp = cur;
            cur = cur->nxt;
            delete(tmp);
        }
        delete head;
    }
    void push(int x) {
        node *ptr = head->nxt;
        node *cur = head;
        while(ptr->val <= x) {
            ptr = (cur = ptr)->nxt;
        }
        cur->nxt = new node{x,ptr};
    }
    int getKth(int x) const{
        node *ptr = head->nxt;
        while(ptr != head && x--) ptr = ptr->nxt;
        if(ptr == head) return -1;
        else            return ptr->val;
    }
    void merge(LinkList *tmp) {
        if(this == tmp) return;
        if(tmp->head->nxt == tmp->head) return;

        node first(0,head);
        node *top = &first;
        node *end1 = head,*top1 = end1->nxt;
        node *end2 = tmp->head,*top2 = end2->nxt;
        while(top1 != end1 || top2 != end2) {
            if(top1 != end1 && (top2 == end2 || top1->val < top2->val)) {
                top = top->nxt = top1;
                top1 = top1->nxt;
            } else {
                top = top->nxt = top2;
                top2 = top2->nxt;
            }
        }
        head->nxt = first.nxt;
        top->nxt  = head;
        tmp->head->nxt = tmp->head;
    }
    void print() const {
        node *cur = head->nxt;
        while(cur != head) {
            std::cout << cur->val << (cur->nxt == head ? '\0' : ' ');
            cur = cur->nxt;
        }
    }
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
    void print() const{
        for(int i = 0 ; i < len ; ++i) {
            std::cout << i  << ':';
            lists[i]->print();
            std::cout << '\n';
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
        std::cout << "Info:\n";
        a.print();
    }
    return 0;
}