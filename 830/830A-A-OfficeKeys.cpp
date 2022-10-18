//url:https://codeforces.com/contest/830/problem/A
//time:2021-03-31 09:00:25
//name:A-OfficeKeys

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
constexpr int inf = 2e9;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k, p;
    std::cin >> n >> k >> p;
    std::vector<int> a(n), b(k);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < k; i++) {
        std::cin >> b[i];
    }
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, inf));
    dp[0][0] = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = i; j <= k - n + i; j++) {
            if (i < n) {
                dp[i + 1][j + 1] = std::min(dp[i + 1][j + 1], std::max(dp[i][j], std::abs(a[i] - b[j]) + std::abs(b[j] - p)));
            }
            if (j < k) {
                dp[i][j + 1] = std::min(dp[i][j + 1], dp[i][j]);
            }
        }
    }
    std::cout << dp[n][k] << "\n";
    return 0;
}

