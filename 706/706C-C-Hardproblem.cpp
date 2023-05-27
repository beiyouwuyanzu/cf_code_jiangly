// url:https://codeforces.com/contest/706/problem/C
// time:2023-03-14 20:46:54
// name:C-Hardproblem

#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> c[i];
    }
    
    std::vector<std::array<std::string, 2>> s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i][0];
        s[i][1] = std::string(s[i][0].rbegin(), s[i][0].rend());
    }
    
    std::array<i64, 2> dp{0, c[0]};
    for (int i = 1; i < n; i++) {
        std::array<i64, 2> g{inf, inf};
        for (int x = 0; x < 2; x++) {
            for (int y = 0; y < 2; y++) {
                if (s[i - 1][x] <= s[i][y]) {
                    g[y] = std::min(g[y], dp[x] + c[i] * y);
                }
            }
        }
        dp = g;
    }
    auto ans = std::min(dp[0], dp[1]);
    if (ans == inf) {
        ans = -1;
    }
    std::cout << ans << "\n";
    
    return 0;
}

