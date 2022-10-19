// url:https://codeforces.com/contest/1644/problem/C
// time:2022-02-23 08:10:39
// name:C-IncreaseSubarraySums

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, x;
    std::cin >> n >> x;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<int> f(n + 1, -1E9);
    f[0] = 0;
    for (int i = 0; i < n; i++) {
        int s = 0;
        for (int j = i; j < n; j++) {
            s += a[j];
            f[j - i + 1] = std::max(f[j - i + 1], s);
        }
    }
    
    for (int k = 0; k <= n; k++) {
        int ans = 0;
        for (int i = 0; i <= n; i++) {
            ans = std::max(ans, f[i] + std::min(k, i) * x);
        }
        std::cout << ans << " \n"[k == n];
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
