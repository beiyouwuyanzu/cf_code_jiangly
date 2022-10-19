// url:https://codeforces.com/contest/1684/problem/D
// time:2022-05-19 17:51:46
// name:D-Traps

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    i64 ans = 0;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        ans += a[i];
        a[i] = n - i - a[i];
    }
    std::sort(a.begin(), a.end());
    for (int i = 0; i < k; i++) {
        ans += a[i];
    }
    ans -= 1LL * k * (k + 1) / 2;
    
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
