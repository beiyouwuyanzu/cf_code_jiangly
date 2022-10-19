// url:https://codeforces.com/contest/1680/problem/A
// time:2022-05-16 16:41:40
// name:A-MinimumsandMaximums

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int l1, r1, l2, r2;
    std::cin >> l1 >> r1 >> l2 >> r2;
    
    if (std::max(l1, l2) <= std::min(r1, r2)) {
        std::cout << std::max(l1, l2) << "\n";
    } else {
        std::cout << l1 + l2 << "\n";
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
