// url:https://codeforces.com/contest/711/problem/C
// time:2023-03-15 10:19:41
// name:C-ColoringTrees

#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, k;
    std::cin >> n >> m >> k;
    
    std::vector<int> c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> c[i];
        c[i]--;
    }
    
    std::vector p(n, std::vector<i64>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> p[i][j];
        }
        if (c[i] != -1) {
            for (int j = 0; j < m; j++) {
                p[i][j] = inf;
            }
            p[i][c[i]] = 0;
        }
    }
    
    std::vector dp(k, std::vector(m, inf));
    dp[0] = p[0];
    
    for (int i = 1; i < n; i++) {
        std::vector newdp(k, std::vector(m, inf));
        for (int j = 0; j < k; j++) {
            for (int x = 0; x < m; x++) {
                for (int y = 0; y < m; y++) {
                    int nj = j + (x != y);
                    if (nj < k) {
                        newdp[nj][y] = std::min(newdp[nj][y], dp[j][x] + p[i][y]);
                    }
                }
            }
        }
        std::swap(dp, newdp);
    }
    
    auto ans = *std::min_element(dp[k - 1].begin(), dp[k - 1].end());
    if (ans == inf) {
        ans = -1;
    }
    std::cout << ans << "\n";
    
    return 0;
}

