// url:https://codeforces.com/contest/1698/problem/B
// time:2022-07-02 11:08:55
// name:B-RisingSand

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    int ans = 0;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    for (int i = 1; i < n - 1; i++) {
        ans += (a[i] > a[i - 1] + a[i + 1]);
    }
    
    if (k == 1) {
        std::cout << (n - 1) / 2 << "\n";
    } else {
        std::cout << ans << "\n";
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
