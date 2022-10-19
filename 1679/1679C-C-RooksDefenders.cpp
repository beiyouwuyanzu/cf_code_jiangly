// url:https://codeforces.com/contest/1679/problem/C
// time:2022-05-16 15:18:10
// name:C-RooksDefenders

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::set<int> r{-1, n}, c{-1, n};
    std::vector<int> cntr(n), cntc(n);
    for (int i = 0; i < n; i++) {
        r.insert(i);
        c.insert(i);
    }
    
    for (int i = 0; i < q; i++) {
        int t;
        std::cin >> t;
        
        if (t == 1) {
            int x, y;
            std::cin >> x >> y;
            x--;
            y--;
            if (++cntr[x]) {
                r.erase(x);
            }
            if (++cntc[y]) {
                c.erase(y);
            }
        } else if (t == 2) {
            int x, y;
            std::cin >> x >> y;
            x--;
            y--;
            if (!--cntr[x]) {
                r.insert(x);
            }
            if (!--cntc[y]) {
                c.insert(y);
            }
        } else {
            int x1, y1, x2, y2;
            std::cin >> x1 >> y1 >> x2 >> y2;
            x1--;
            y1--;
            x2--;
            y2--;
            
            if (*r.lower_bound(x1) > x2 || *c.lower_bound(y1) > y2) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        }
    }
    
    return 0;
}
