// url:https://codeforces.com/contest/112/problem/E
// time:2023-04-27 11:45:06
// name:E-PetyaandSpiders

#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1E9;

void chmin(int &a, int b) {
    if (a > b) {
        a = b;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    if (n < m) {
        std::swap(n, m);
    }
    
    std::vector dp(1 << (2 * m), 0);
    
    for (int x = 0; x < n; x++) {
        auto g = dp;
        for (int u = 0; u < (1 << m); u++) {
            for (int v = 0; v < (1 << m); v++) {
                dp[u << m | v] = g[v << m | u];
            }
        }
        for (int y = 0; y < m; y++) {
            std::vector g(1 << (2 * m), inf);
            for (int s = 0; s < (1 << (2 * m)); s++) {
                if (s >> (m + y) & 1) {
                    chmin(g[s], dp[s ^ 1 << (m + y)]);
                } else {
                    chmin(g[s], dp[s | 1 << y | 1 << (m + y)] + 1);
                    if (y) {
                        chmin(g[s], dp[s | 1 << (m + y - 1) | 1 << (y - 1)] + 1);
                        chmin(g[s], dp[s | 1 << (m + y - 1) | 1 << y] + 1);
                        chmin(g[s], dp[s | 1 << (m + y) | 1 << y | 1 << (y - 1)] + 1);
                    }
                    if (y < m - 1) {
                        chmin(g[s], dp[s | 1 << (m + y) | 1 << y | 1 << (y + 1)] + 1);
                    }
                    if (y && y < m - 1) {
                        chmin(g[s], dp[s | 1 << (m + y) | 1 << y | 1 << (y - 1) | 1 << (y + 1)] + 1);
                    }
                    if (y >= 2) {
                        chmin(g[s], dp[s | 1 << (m + y - 1) | 1 << (m + y - 2) | 1 << (y - 1)] + 1);
                    }
                }
            }
            std::swap(dp, g);
        }
    }
    
    int ans = n * m - dp[0];
    std::cout << ans << "\n";
    
    return 0;
}
