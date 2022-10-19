// url:https://codeforces.com/contest/1542/problem/E1
// time:2021-07-03 16:58:37
// name:E1-AbnormalPermutationPairs(easyversion)

#include <bits/stdc++.h>
using i64 = long long;
int mod;
int norm(int x) {
    if (x < mod) {
        return x;
    } else {
        return x - mod;
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n >> mod;
    int m = n * (n - 1) / 2;
    std::vector<int> dp(2 * m + 1);
    dp[m] = 1 % mod;
    int ans = 0;
    int s = 0;
    for (int i = 1; i <= n; i++) {
        int res = 0;
        for (int j = 1; j <= s; j++) {
            int w = std::min(j, i);
            res = (res + i64(i * (i - 1) / 2 - (i - w) * (i - w + 1) / 2) * dp[m + j]) % mod;
        }
        for (int j = i + 1; j <= n; j++) {
            res = i64(res) * j % mod;
        }
        ans = norm(ans + res);
        s += i - 1;
        for (int j = s; j - i >= -s; j--) {
            dp[m + j] = norm(dp[m + j] + mod - dp[m + j - i]);
        }
        for (int j = -s + 1; j <= s; j++) {
            dp[m + j] = norm(dp[m + j] + dp[m + j - 1]);
        }
        for (int j = -s; j + i <= s; j++) {
            dp[m + j] = norm(dp[m + j] + mod - dp[m + j + i]);
        }
        for (int j = s - 1; j >= -s; j--) {
            dp[m + j] = norm(dp[m + j] + dp[m + j + 1]);
        }
    }
    std::cout << ans << "\n";
    return 0;
}
