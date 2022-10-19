// url:https://codeforces.com/contest/1638/problem/C
// time:2022-02-14 19:03:34
// name:C-InversionGraph

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        b[i] = a[i];
        if (i > 0) {
            a[i] = std::max(a[i], a[i - 1]);
        }
    }
    
    for (int i = n - 2; i >= 0; i--) {
        b[i] = std::min(b[i], b[i + 1]);
    }
    
    int ans = 1;
    for (int i = 0; i < n - 1; i++) {
        ans += (a[i] < b[i + 1]);
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
