// url:https://codeforces.com/contest/1741/problem/E
// time:2022-10-11 17:53:03
// name:E-SendingaSequenceOvertheNetwork

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<int> dp(n + 1);
    dp[0] = 1;
    for (int i = 0; i <= n; i++) {
        if (i && i - 1 - a[i - 1] >= 0) {
            dp[i] |= dp[i - 1 - a[i - 1]];
        }
        if (i < n && i + a[i] + 1 <= n) {
            dp[i + a[i] + 1] |= dp[i];
        }
    }
    
    if (dp[n]) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
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

