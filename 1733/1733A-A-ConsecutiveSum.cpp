//url:https://codeforces.com/contest/1733/problem/A
//time:2022-09-19 17:37:51
//name:A-ConsecutiveSum

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    for (int i = k; i < n; i++) {
        a[i % k] = std::max(a[i % k], a[i]);
    }
    
    i64 ans = std::accumulate(a.begin(), a.begin() + k, 0LL);
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
