//url:https://codeforces.com/contest/1470/problem/E
//time:2021-01-05 18:58:36
//name:E-StrangePermutation

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n, c, q;
        std::cin >> n >> c >> q;
        std::vector<int> p(n);
        for (int i = 0; i < n; i++) {
            std::cin >> p[i];
            p[i]--;
        }
        std::vector<std::vector<i64>> dp(n + 1, std::vector<i64>(c + 1));
        for (int i = 0; i <= c; i++) {
            dp[n][i] = 1;
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j <= c; j++) {
                for (int k = 0; k <= j && i + k < n; k++) {
                    dp[i][j] += dp[i + k + 1][j - k];
                }
            }
        }
        std::vector<std::vector<int>> s(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= c && i + j < n; j++) {
                s[i].push_back(j);
            }
            std::sort(s[i].begin(), s[i].end(), [&](int x, int y) {
                return p[i + x] < p[i + y];
            });
        }
        std::vector<std::vector<std::vector<i64>>> L(n), R(n);
        int lg = std::__lg(n);
        for (int i = 0; i < n; i++) {
            L[i].assign(c + 1, std::vector<i64>(lg + 1));
            R[i].assign(c + 1, std::vector<i64>(lg + 1));
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j <= c; j++) {
                i64 sum = 0;
                for (auto x : s[i]) {
                    if (x > j) {
                        continue;
                    }
                    if (x == 0) {
                        break;
                    }
                    sum += dp[i + x + 1][j - x];
                }
                L[i][j][0] = sum;
                R[i][j][0] = sum + dp[i + 1][j];
                for (int k = 1; i + (1 << k) <= n; k++) {
                    L[i][j][k] = L[i][j][k - 1] + L[i + (1 << (k - 1))][j][k - 1];
                    R[i][j][k] = L[i][j][k - 1] + R[i + (1 << (k - 1))][j][k - 1];
                }
            }
        }
        while (q--) {
            int pos;
            i64 y;
            std::cin >> pos >> y;
            pos--;
            y--;
            int i = 0;
            int r = c;
            int ans = p[pos];
            if (y >= dp[0][c]) {
                std::cout << -1 << "\n";
                continue;
            }
            while (i < n) {
                for (int j = lg; j > 0; j--) {
                    if (i + (1 << j) <= n && L[i][r][j] <= y && y < R[i][r][j]) {
                        y -= L[i][r][j];
                        i += 1 << j;
                    }
                }
                if (i == n) {
                    break;
                }
                for (auto x : s[i]) {
                    if (x > r) {
                        continue;
                    }
                    if (y >= dp[i + x + 1][r - x]) {
                        y -= dp[i + x + 1][r - x];
                    } else {
                        int i1 = i + x;
                        if (i <= pos && pos <= i1) {
                            ans = p[i + i1 - pos];
                        }
                        i += x + 1;
                        r -= x;
                        break;
                    }
                }
            }
            std::cout << ans + 1 << "\n";
        }
    }
    return 0;
}
