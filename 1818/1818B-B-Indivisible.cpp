// url:https://codeforces.com/contest/1818/problem/B
// time:2023-04-29 21:45:44
// name:B-Indivisible

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    if (n == 1) {
        std::cout << 1 << "\n";
    } else if (n % 2) {
        std::cout << -1 << "\n";
    } else {
        for (int i = 0; i < n; i++) {
            std::cout << (i ^ 1) + 1 << " \n"[i == n - 1];
        }
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
