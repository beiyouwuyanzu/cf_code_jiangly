// url:https://codeforces.com/contest/339/problem/C
// time:2023-04-28 19:53:48
// name:C-XeniaandWeights

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s;
    int m;
    std::cin >> s >> m;
    
    std::vector dp(m + 1, std::vector(11, std::vector(10, -1)));
    
    dp[0][0][0] = dp[0][0][1] = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= 10; j++) {
            for (int x = 0; x < 10; x++) {
                for (int y = 0; y < 10; y++) {
                    if (x != y && s[y] == '1' && y + 1 - j > 0 && dp[i][j][x] != -1) {
                        dp[i + 1][y + 1 - j][y] = x;
                    }
                }
            }
        }
    }
    
    for (int j = 0; j <= 10; j++) {
        for (int x = 0; x < 10; x++) {
            if (dp[m][j][x] != -1) {
                std::cout << "YES\n";
                std::vector<int> ans;
                for (int i = m; i; i--) {
                    ans.push_back(x + 1);
                    int y = dp[i][j][x];
                    j = x + 1 - j;
                    x = y;
                }
                std::reverse(ans.begin(), ans.end());
                for (int i = 0; i < m; i++) {
                    std::cout << ans[i] << " \n"[i == m - 1];
                }
                return 0;
            }
        }
    }
    
    std::cout << "NO\n";
    
    return 0;
}
