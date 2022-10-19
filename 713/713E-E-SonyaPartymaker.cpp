// url:https://codeforces.com/contest/713/problem/E
// time:2021-07-07 17:06:19
// name:E-SonyaPartymaker

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int m;
    std::cin >> m;
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n + 1);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
    }
    for (int i = n - 1; i >= 0; i--) {
        a[i] -= a[0];
    }
    a[n] = m;
    
    auto solve = [&]() {
        int lo = 0, hi = 0;
        for (int i = 0; i < n; i++) {
            hi = std::max(hi, a[i + 1] - a[i] - 1);
        }
        
        auto get = [&](int s, int x) {
            std::vector<int> dp(n + 1, -m);
            dp[s] = x;
            for (int i = s; i < n - 1; i++) {
                if (dp[i] >= a[i + 1] - 1) {
                    dp[i + 1] = std::max(dp[i + 1], a[i + 1] + x);
                }
                if (dp[i] >= a[i + 1] - x - 1) {
                    dp[i + 1] = std::max(dp[i + 1], a[i + 1]);
                }
                if (dp[i] >= a[i + 2] - x - 1) {
                    dp[i + 2] = std::max(dp[i + 2], a[i + 1] + x);
                }
            }
            return dp[n - 1];
        };
    
        while (lo < hi) {
            int x = (lo + hi) / 2;
            if (get(0, x) >= m - 1 || (a[1] < x && get(1, x) >= m - x + a[1] - 1)) {
                hi = x;
            } else {
                lo = x + 1;
            }
        }
        
        return lo;
    };
    
    int ans = solve();
    std::reverse(a.begin() + 1, a.begin() + n);
    for (int i = 1; i < n; i++) {
        a[i] = m - a[i];
    }
    ans = std::min(ans, solve());
    
    std::cout << ans << "\n";
    
    return 0;
}
