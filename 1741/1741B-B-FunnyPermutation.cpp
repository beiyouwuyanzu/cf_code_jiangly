// url:https://codeforces.com/contest/1741/problem/B
// time:2022-10-11 17:43:35
// name:B-FunnyPermutation

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    if (n == 3) {
        std::cout << -1 << "\n";
        return;
    }
    if (n == 2) {
        std::cout << 2 << " " << 1 << "\n";
        return;
    }
    
    for (int i = 0; i < n; i++) {
        std::cout << (i + 2) % n + 1 << " \n"[i == n - 1];
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

