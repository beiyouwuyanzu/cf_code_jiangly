// url:https://codeforces.com/contest/1823/problem/B
// time:2023-04-28 08:43:25
// name:B-SortwithStep

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        x--;
        cnt += (x % k != i % k);
    }
    if (cnt > 2) {
        std::cout << -1 << "\n";
        return;
    }
    std::cout << cnt / 2 << "\n";
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
