// url:https://codeforces.com/contest/1736/problem/E
// time:2022-10-10 20:30:15
// name:E-SwapandTake

#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1E9;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n + 1);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector dp(n + 1, std::vector<int>(n + 2, -inf));
    dp[0][1] = 0;
    
    for (int i = 0; i < n; i++) {
        for (int k = 1; k <= i + 1; k++) {
            int t = -inf;
            for (int j = 0; j <= n; j++) {
                t = std::max(t, dp[j][k]);
            }
            for (int j = i + 1; j < n && j - i <= k; j++) {
                dp[j][k - (j - i)] = std::max(dp[j][k - (j - i)], t);
            }
        }
        for (int k = i + 1; k >= 0; k--) {
            for (int j = n - 1; j >= 0; j--) {
                dp[j][k] += a[j];
                if (j <= i) {
                    dp[i + 1][k + 1] = std::max(dp[i + 1][k + 1], dp[j][k]);
                }
                dp[n][k + 1] = std::max(dp[n][k + 1], dp[j][k]);
            }
        }
    }
    
    int ans = 0;
    for (int j = 0; j <= n; j++) {
        for (int k = 0; k <= n + 1; k++) {
            ans = std::max(ans, dp[j][k]);
        }
    }
    std::cout << ans << "\n";
    
    return 0;
}

