//url:https://codeforces.com/contest/1739/problem/E
//time:2022-09-29 18:20:25
//name:E-CleaningRobot

#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1E9;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector a(2, std::vector<int>(n + 2));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            char ch;
            std::cin >> ch;
            a[i][j] = ch - '0';
        }
    }
    
    std::vector dp(2, std::vector<int>(n + 1, -inf));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            dp[j][i + 1] = std::max(dp[j][i + 1], dp[j][i] + a[j][i + 1]);
            int t = std::min(i + 2, n);
            if (a[!j][i]) {
                dp[!j][t] = std::max(dp[!j][t], dp[j][i] + 1 + a[!j][i + 1] + a[!j][i + 2]);
            }
        }
    }
    
    std::cout << std::max(dp[0][n], dp[1][n]) << "\n";
    
    return 0;
}
