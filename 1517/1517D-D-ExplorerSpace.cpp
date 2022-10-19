// url:https://codeforces.com/contest/1517/problem/D
// time:2021-04-23 18:15:41
// name:D-ExplorerSpace

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
void upd(int &a, int b) {
    if (b < a) {
        a = b;
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, k;
    std::cin >> n >> m >> k;
    if (k % 2 == 1) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                std::cout << -1 << " \n"[j == m - 1];
            }
        }
        return 0;
    }
    std::vector<std::vector<int>> a(n, std::vector<int>(m - 1)), b(n - 1, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            std::cin >> a[i][j];
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> b[i][j];
        }
    }
    k /= 2;
    for (int X = 0; X < n; X++) {
        for (int Y = 0; Y < m; Y++) {
            int dp[2][21][21] {};
            std::memset(dp, 0x3f, sizeof(dp));
            dp[0][k][k] = 0;
            int cur = 0;
            for (int t = 0; t < k; t++) {
                std::memset(dp[!cur], 0x3f, sizeof(dp[!cur]));
                for (int x = std::max(0, X - t); x <= X + t && x < n; x++) {
                    int d = t - std::abs(X - x);
                    for (int y = std::max(0, Y - d); y <= Y + d && y < m; y++) {
                        int v = dp[cur][x - X + k][y - Y + k];
                        if (x > 0) {
                            upd(dp[!cur][x - 1 - X + k][y - Y + k], v + b[x - 1][y]);
                        }
                        if (x < n - 1) {
                            upd(dp[!cur][x + 1 - X + k][y - Y + k], v + b[x][y]);
                        }
                        if (y > 0) {
                            upd(dp[!cur][x - X + k][y - 1 - Y + k], v + a[x][y - 1]);
                        }
                        if (y < m - 1) {
                            upd(dp[!cur][x - X + k][y + 1 - Y + k], v + a[x][y]);
                        }
                    }
                }
                cur ^= 1;
            }
            int ans = 1e9;
            for (int i = 0; i <= 2 * k; i++) {
                for (int j = 0; j <= 2 * k; j++) {
                    ans = std::min(ans, dp[cur][i][j]);
                }
            }
            std::cout << 2 * ans << " \n"[Y == m - 1];
        }
    }
    return 0;
}
