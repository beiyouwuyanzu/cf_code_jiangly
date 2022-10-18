//url:https://codeforces.com/contest/1096/problem/D
//time:2021-07-15 20:48:27
//name:D-EasyProblem

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<i64> dp(4);
    for (int i = 0; i < n; i++) {
        std::vector<i64> g(4, 1e18);
        for (int j = 0; j < 4; j++) {
            if (j < 3) {
                g[j + 1] = std::min(g[j + 1], dp[j]);
            }
            g[j] = std::min(g[j], dp[j] + (s[i] == "hard"[j] ? a[i] : 0));
        }
        
        dp = g;
    }
    
    i64 ans = *std::min_element(dp.begin(), dp.end());
    std::cout << ans << "\n";
    
    return 0;
}
