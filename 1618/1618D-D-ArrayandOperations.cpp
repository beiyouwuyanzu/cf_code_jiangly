// url:https://codeforces.com/contest/1618/problem/D
// time:2021-12-22 10:23:44
// name:D-ArrayandOperations

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end(), std::greater());
    
    int ans = 0;
    for (int i = 0; i < k; i++) {
        ans += a[i + k] / a[i];
    }
    ans += std::accumulate(a.begin() + 2 * k, a.end(), 0);
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
