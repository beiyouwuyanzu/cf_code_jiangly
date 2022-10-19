// url:https://codeforces.com/contest/1515/problem/E
// time:2021-05-02 17:57:23
// name:E-PhoenixandComputers

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, M;
    std::cin >> n >> M;
    std::vector<std::vector<int>> dp(n + 2, std::vector<int>(n + 2));
    dp[0][0] = 1;
    std::vector<std::vector<int>> binom(n + 2, std::vector<int>(n + 2));
    std::vector<int> pow2(n + 2);
    pow2[0] = 1;
    for (int i = 1; i <= n + 1; i++) {
        pow2[i] = pow2[i - 1] * 2 % M;
    }
    for (int i = 0; i <= n + 1; i++) {
        binom[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % M;
        }
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n + 1; j++) {
            if (dp[i][j] == 0) {
                continue;
            }
            for (int k = 1; i + k <= n; k++) {
                dp[i + k + 1][j + k] = (dp[i + k + 1][j + k] + i64(dp[i][j]) * pow2[k - 1] % M * binom[j + k][j]) % M;
            }
        }
    }
    int ans = std::accumulate(dp[n + 1].begin(), dp[n + 1].end(), 0ll) % M;
    std::cout << ans << "\n";
    return 0;
}
