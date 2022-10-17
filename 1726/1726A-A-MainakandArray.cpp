//url:https://codeforces.com/contest/1726/problem/A
//time:2022-09-06 17:38:04
//name:A-MainakandArray

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    int ans = a[n - 1] - a[0];
    for (int i = 0; i < n; i++) {
        ans = std::max(ans, a[i] - a[(i + 1) % n]);
    }
    
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            ans = std::max(ans, a[i] - a[0]);
        }
        if (i < n - 1) {
            ans = std::max(ans, a[n - 1] - a[i]);
        }
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
