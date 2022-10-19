// url:https://codeforces.com/contest/1743/problem/E
// time:2022-10-17 18:09:09
// name:E-FTL

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int p1, p2, h, s;
    i64 t1, t2;
    
    std::cin >> p1 >> t1 >> p2 >> t2 >> h >> s;
    
    std::vector<i64> dp(h + 1);
    dp[0] = 0;
    for (int i = 1; i <= h; i++) {
        dp[i] = std::min(dp[std::max(0, i - (p1 - s))] + t1, dp[std::max(0, i - (p2 - s))] + t2);
        for (int j = 1; j <= i; j++) {
            if (j * t1 >= t2) {
                i64 dmg = (j - 1) * (p1 - s) + (j * t1 - t2) / t2 * (p2 - s) + (p1 + p2 - s);
                dp[i] = std::min(dp[i], dp[std::max(0LL, i - dmg)] + j * t1);
            }
            if (j * t2 >= t1) {
                i64 dmg = (j - 1) * (p2 - s) + (j * t2 - t1) / t1 * (p1 - s) + (p1 + p2 - s);
                dp[i] = std::min(dp[i], dp[std::max(0LL, i - dmg)] + j * t2);
            }
        }
    }
    std::cout << dp[h] << "\n";
    
    return 0;
}
