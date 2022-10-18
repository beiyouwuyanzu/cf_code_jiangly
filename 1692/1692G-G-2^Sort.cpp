//url:https://codeforces.com/contest/1692/problem/G
//time:2022-06-14 17:49:20
//name:G-2^Sort

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    int cur = 0, ans = 0;
    for (int i = 0; i < n - 1; i++) {
        if (a[i] < 2 * a[i + 1]) {
            cur++;
            ans += (cur >= k);
        } else {
            cur = 0;
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

