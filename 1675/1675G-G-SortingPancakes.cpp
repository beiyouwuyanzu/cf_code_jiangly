// url:https://codeforces.com/contest/1675/problem/G
// time:2022-05-05 19:23:34
// name:G-SortingPancakes

#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1E9;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<int> s(n + 1);
    for (int i = 0; i < n; i++) {
        s[i + 1] = s[i] + a[i];
    }
    
    std::vector dp(n + 1, std::vector<int>(m + 1, inf));
    dp[0][0] = 0;
    for (int x = m; x >= 0; x--) {
        for (int j = 0; j <= m - x; j++) {
            for (int i = 0; i < n && i * x <= j; i++) {
                dp[i + 1][j + x] = std::min(dp[i + 1][j + x], dp[i][j] + std::abs(j - s[i]));
            }
        }
    }
    
    std::cout << dp[n][m] << "\n";
    
    return 0;
}
