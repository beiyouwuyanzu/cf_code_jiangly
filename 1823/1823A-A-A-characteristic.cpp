// url:https://codeforces.com/contest/1823/problem/A
// time:2023-04-28 08:40:27
// name:A-A-characteristic

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    for (int c = 0; c <= n; c++) {
        int res = c * (c - 1) / 2 + (n - c) * (n - c - 1) / 2;
        if (res == k) {
            std::cout << "YES\n";
            for (int i = 0; i < n; i++) {
                std::cout << (i < c ? 1 : -1) << " \n"[i == n - 1];
            }
            return;
        }
    }
    std::cout << "NO\n";
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
