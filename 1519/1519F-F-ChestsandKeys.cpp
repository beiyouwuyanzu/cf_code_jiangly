// url:https://codeforces.com/contest/1519/problem/F
// time:2022-06-27 13:11:07
// name:F-ChestsandKeys

#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        std::cin >> b[i];
    }
    
    if (std::accumulate(a.begin(), a.end(), 0) > std::accumulate(b.begin(), b.end(), 0)) {
        std::cout << "-1\n";
        return 0;
    }
    
    std::vector<int> p(n + 1);
    p[0] = 1;
    for (int i = 0; i < n; i++) {
        p[i + 1] = p[i] * (a[i] + 1);
    }
    
    std::vector<i64> dp(p[n], inf);
    dp[p[n] - 1] = 0;
    
    std::vector c(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> c[i][j];
        }
    }
    
    for (int j = 0; j < m; j++) {
        std::vector g(p[n], std::vector<i64>(b[j] + 1));
        for (int s = 0; s < p[n]; s++) {
            g[s].assign(b[j] + 1, dp[s]);
        }
        
        for (int i = 0; i < n; i++) {
            for (int s = 0; s < p[n]; s++) {
                int x = s / p[i] % (a[i] + 1);
                for (int y = 0; y <= b[j]; y++) {
                    for (int t = 1; t <= std::min(x, y); t++) {
                        i64 ns = s - p[i] * t;
                        g[ns][y - t] = std::min(g[ns][y - t], g[s][y] + c[i][j]);
                    }
                }
            }
        }
        
        for (int s = 0; s < p[n]; s++) {
            dp[s] = g[s][0];
        }
    }
    
    std::cout << dp[0] << "\n";
    
    return 0;
}

