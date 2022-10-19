// url:https://codeforces.com/contest/1621/problem/B
// time:2022-01-03 17:43:12
// name:B-IntegersShop

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    int L = 2E9, R = 0;
    int cl = 2E9, cr = 2E9;
    
    int all = 2E9;
    
    for (int i = 0; i < n; i++) {
        int l, r, c;
        std::cin >> l >> r >> c;
        
        bool change = false;
        if (l < L) {
            L = l;
            cl = c;
            change = true;
        } else if (l == L) {
            cl = std::min(cl, c);
        }
        if (r > R) {
            R = r;
            cr = c;
            change = true;
        } else if (r == R) {
            cr = std::min(cr, c);
        }
        
        if (change) {
            all = 2E9;
        }
        if (l == L && r == R) {
            all = std::min(all, c);
        }
        std::cout << std::min(cl + cr, all) << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}

