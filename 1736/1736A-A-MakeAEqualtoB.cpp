// url:https://codeforces.com/contest/1736/problem/A
// time:2022-10-10 18:39:51
// name:A-MakeAEqualtoB

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n), b(n);
    for (auto &i : a) {
        std::cin >> i;
    }
    for (auto &i : b) {
        std::cin >> i;
    }
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += a[i] ^ b[i];
    }
    
    ans = std::min(ans, int(std::abs(std::count(a.begin(), a.end(), 1) - std::count(b.begin(), b.end(), 1)) + 1));
    std::cout << ans << "\n";
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

