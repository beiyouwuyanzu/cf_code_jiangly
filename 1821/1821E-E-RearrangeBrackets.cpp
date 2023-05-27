// url:https://codeforces.com/contest/1821/problem/E
// time:2023-04-20 19:28:34
// name:E-RearrangeBrackets

#include <bits/stdc++.h>

using i64 = long long;

void chmin(i64 &a, i64 b) {
    if (a > b) {
        a = b;
    }
}

void solve() {
    int k;
    std::cin >> k;
    
    std::string s;
    std::cin >> s;
    
    int n = s.size() / 2;
    
    std::vector<int> pre(2 * n + 1);
    for (int i = 0; i < 2 * n; i++) {
        pre[i + 1] = pre[i] + (s[i] == '(' ? 1 : -1);
    }
    
    i64 dp[6][6][6][6] {};
    std::memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0][0] = 0;
    
    for (int i = 0; i <= 2 * n; i++) {
        if (i) {
            for (int a = k; a >= 0; a--) {
                for (int b = k; b >= 0; b--) {
                    for (int c = k - std::max(a, b); c >= 0; c--) {
                        for (int d = k - std::max(a, b); d >= 0; d--) {
                            if (b < k && pre[i] - a + (b + 1) + c - d >= 0) {
                                chmin(dp[a][b + 1][c][d], dp[a][b][c][d] + pre[i] - a + (b + 1) + c - d);
                            }
                            if (d < k && pre[i] - a + b + c - (d + 1) >= 0) {
                                chmin(dp[a][b][c][d + 1], dp[a][b][c][d] + pre[i] - a + b + c - (d + 1));
                            }
                            if (pre[i] - a + b + c - d < 0) {
                                dp[a][b][c][d] = 0x3f3f3f3f3f3f3f3f;
                            } else {
                                dp[a][b][c][d] += pre[i] - a + b + c - d;
                            }
                        }
                    }
                }
            }
        }
        for (int a = 0; a <= k; a++) {
            for (int b = 0; b <= k; b++) {
                for (int c = 0; c <= k - std::max(a, b); c++) {
                    for (int d = 0; d <= k - std::max(a, b); d++) {
                        if (a < k && pre[i] - (a + 1) + b + c - d >= 0) {
                            chmin(dp[a + 1][b][c][d], dp[a][b][c][d] + pre[i] - (a + 1) + b + c - d);
                        }
                        if (c < k && pre[i] - a + b + (c + 1) - d >= 0) {
                            chmin(dp[a][b][c + 1][d], dp[a][b][c][d] + pre[i] - a + b + (c + 1) - d);
                        }
                    }
                }
            }
        }
    }
    
    i64 ans = 0x3f3f3f3f3f3f3f3f;
    for (int a = 0; a <= k; a++) {
        for (int b = 0; a + b <= k; b++) {
            ans = std::min(ans, dp[a][a][b][b]);
        }
    }
    ans = (ans - n) / 2;
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
