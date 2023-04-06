#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 3e5 + 3;
const int M = 399;
const int S = N / M + 9;


struct point { double x,y; };

inline int index(int x) { return (x - 1) / M; }

vector <point> dat[S];
vector <point> cov[S];
vector <point> st;
point arr[N];

inline bool comp(point p) {
    point p1 = st.back();
    point p2 = *++st.rbegin();
    return (p1.y - p2.y) * (p.x - p1.x) <= (p.y - p1.y) * (p1.x - p2.x);
}

void get_cov(int x) {
    st.clear();
    const vector <point> & v = dat[x];
    auto iter = v.begin();
    st.push_back(*iter);
    ++iter;
    st.push_back(*iter);
    ++iter;
    while(iter != v.end()) {
        if(iter + 1 == v.end()) {
            cout << "Test\n";
        }
        while(st.size() >= 2 && comp(*iter)) st.pop_back();
        st.push_back(*iter);
        ++iter;
    }
    st.swap(cov[x]);
}

void prework(int x) {
    vector <point> & v = dat[x];
    if(v.size() == 1) return cov[x].push_back(dat[x].front());
    sort(v.begin(),v.end(),[](const point &lhs,const point &rhs){
        return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y > rhs.y;
    });
    for(auto &&iter : dat[0]) cout << iter.x << ' ' << iter.y << '\n';
    get_cov(x);
}

void modify(int t,int x,int y) {

}

double query(int t,double k) {

}

signed main() {
    int n,m;
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 1 ; i <= n ; ++i) {
        cin >> arr[i].x >> arr[i].y;
        dat[index(i)].push_back(arr[i]);
    }
    for(int i = index(n) ; i >= 0 ; --i) prework(i);
    while(m--) {
        char opt;
        cin >> opt;
        if(opt == 1) {
            cin >> opt;
            cin >> arr[opt].x >> arr[opt].y;
            modify(opt,x,y);
        } else {
            double k;
            cin >> k;
            double ans = -1145141919810;
            for(int i = index(n) ; i >= 0 ; --i) ans = max(ans,)
            cout << fixed << setprecision(2) << dist(t[loc]) ;
        }
    }

    return 0;
}