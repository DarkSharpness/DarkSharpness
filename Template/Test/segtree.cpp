#include <bits/stdc++.h>
#include <Dark/OI>

dark::segment_tree <int,12> t;

signed main() {
    t.build(10);
    t.add(1,3,1);
    t.add(2,5,3);
    dark::write(t.sum(1,2));
    return 0;
}