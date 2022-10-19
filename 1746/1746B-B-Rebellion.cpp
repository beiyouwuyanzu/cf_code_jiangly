// url:https://codeforces.com/contest/1746/problem/B
// time:2022-10-15 17:45:42
// name:B-Rebellion

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    int c1 = 0, c0 = std::count(a.begin(), a.end(), 0);
    int ans = c0;
    for (int i = 0; i < n; i++) {
        c1 += a[i];
        c0 -= !a[i];
        ans = std::min(ans, std::max(c0, c1));
    }
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
