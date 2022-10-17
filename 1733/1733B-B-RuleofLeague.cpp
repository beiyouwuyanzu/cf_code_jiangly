//url:https://codeforces.com/contest/1733/problem/B
//time:2022-09-19 17:40:46
//name:B-RuleofLeague

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, x, y;
    std::cin >> n >> x >> y;
    
    if (x > y) {
        std::swap(x, y);
    }
    if (x != 0) {
        std::cout << -1 << "\n";
        return;
    }
    
    if (y == 0 || (n - 1) % y != 0) {
        std::cout << -1 << "\n";
        return;
    }
    
    for (int i = 0; i < n - 1; i++) {
        std::cout << i - i % y + 2 << " \n"[i == n - 2];
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
