// url:https://codeforces.com/contest/598/problem/E
// time:2023-04-23 21:03:15
// name:E-ChocolateBar

#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 30, K = 50;

int dp[N+1][N+1][K+1];

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;
    
    std::cout << dp[n][m][k] << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::memset(dp, 0x3f, sizeof(dp));
    for (int n = 1; n <= N; n++) {
        for (int m = 1; m <= N; m++) {
            dp[n][m][0] = 0;
            if (n*m <= K) {
                dp[n][m][n*m] = 0;
            }
            for (int x = 1; x < n; x++) {
                for (int a = 0; a <= K; a++) {
                    for (int b = 0; a+b <= K; b++) {
                        dp[n][m][a+b] = std::min(dp[n][m][a+b], dp[x][m][a] + dp[n-x][m][b] + m*m);
                    }
                }
            }
            for (int x = 1; x < m; x++) {
                for (int a = 0; a <= K; a++) {
                    for (int b = 0; a+b <= K; b++) {
                        dp[n][m][a+b] = std::min(dp[n][m][a+b], dp[n][x][a] + dp[n][m-x][b] + n*n);
                    }
                }
            }
        }
    }
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
