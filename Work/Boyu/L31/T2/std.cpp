#include <iostream>
#include <queue>
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    queue <long long> q,t;
    long long delta = 0;
    while(n--) {
        long long x;
        cin >> x;
        q.push(x);
    }
    while(m--) {
        long long x;
        cin >> x;
        switch(x) {
            case 1:
                cin >> x;
                delta += x;
                break;
            case 2:
                t.push(q.front());
                q.pop();
                break;
            case 3:
                while(t.size() && t.front() < q.front() + delta)
                    t.pop();
                break;
            case 4:
                cout << t.front() << endl;
                break;
        }
    }
    return 0;
}
