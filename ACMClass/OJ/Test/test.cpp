#include<iostream>
using namespace std;

struct LinkedList {
    struct node{
        node * nxt;
        int    val; 
        node(int Val) {
            val = Val;
            nxt = nullptr;
        }
        ~node() {

        }
    };
    using nodeptr = node *;
    nodeptr pre_head;

    // todo: some variables here
    void initialize() {
        int n;
        scanf("%d", &n);
        int *a = new int[n];
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        nodeptr now = pre_head;
        for(int i = 0; i < n; ++i) {
            now -> nxt = new node(a[i]);
            now = now ->nxt;
        }
        delete[] a;
    }

    void insert(int i, int x) {
        nodeptr now = pre_head;
        while(i--) now = now->nxt;
        nodeptr tmp = new node(x);
        tmp -> nxt = now ->nxt;
        now -> nxt = tmp;
    }

    void erase(int i) {
        nodeptr now = pre_head;
        while(--i) now = now->nxt;
        nodeptr tmp = now->nxt;
        now->nxt = tmp ->nxt;
        delete(tmp);
    }

    void swap() {
        nodeptr now = pre_head;
        while(now->nxt != nullptr && now->nxt->nxt != nullptr) {
            std::swap(now->nxt->nxt->val,now->nxt->val);//这么写只适用于本题
            now = now ->nxt->nxt;
        }
    }

    void moveback(int i, int x) {
        nodeptr now = pre_head;
        nodeptr head = now->nxt;
        while(i--) {
            now = now -> nxt;
        }
        nodeptr tmp = now;
        while(x--) {
            tmp = tmp ->nxt;
        }
        pre_head->nxt = now->nxt;
        now -> nxt = tmp ->nxt;
        tmp -> nxt = head;
    }

    int query(int i) {
        nodeptr now = pre_head;
        while(i--) {
            now = now ->nxt;
        }
        return now->val;
    }

    void printAll() {
        nodeptr now = pre_head->nxt;
        while(now != nullptr) {
            printf("%d ",now->val);
            now = now ->nxt;
        }
        puts("");
    }

    void ClearMemory() {
        nodeptr now = pre_head;
        while(now != nullptr) {
            nodeptr tmp = now;
            now = now ->nxt;
            delete tmp;
        }
    }
    LinkedList() {
        pre_head = new node(0);
    }
};

int main() {
    LinkedList List;
    int m, op, i, x;
    List.initialize();
    scanf("%d", &m);
    while(m--) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d", &i, &x);
            List.insert(i, x);
        }
        else if(op == 2) {
            scanf("%d", &i);
            List.erase(i);
        }
        else if(op == 3) {
            List.swap();
        }
        else if(op == 4) {
            scanf("%d%d",&i, &x);
            List.moveback(i, x);
        }
        else if(op == 5) {
            scanf("%d", &i);
            printf("%d\n", List.query(i));
        }
        else if(op == 6) {
            List.printAll();
        }
    }
    List.ClearMemory();
    return 0;
}