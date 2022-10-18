//url:https://codeforces.com/contest/1525/problem/D
//time:2022-06-22 17:38:22
//name:D-Armchairs

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<int> dp(2 * n + 1, 1E9);
    dp[n] = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 1) {
            for (int j = 2 * n; j > 0; j--) {
                dp[j] = dp[j - 1];
            }
            dp[0] = 1E9;
        } else {
            for (int j = 0; j < 2 * n; j++) {
                dp[j] = std::min(dp[j], dp[j + 1]);
            }
        }
        for (int j = 0; j <= 2 * n; j++) {
            dp[j] += std::abs(j - n);
        }
    }
    
    std::cout << dp[n] << "\n";
    
    return 0;
}

