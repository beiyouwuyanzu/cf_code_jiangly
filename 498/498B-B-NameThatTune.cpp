// url:https://codeforces.com/contest/498/problem/B
// time:2021-06-21 21:38:37
// name:B-NameThatTune

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, T;
    std::cin >> n >> T;
    std::vector<int> p(n), t(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i] >> t[i];
    }
    std::vector dp(2, std::vector<double>(T + 1));
    for (int i = n - 1; i >= 0; i--) {
        dp[1].assign(T + 1, 0);
        double v = 0, c = 1;
        double pr = 0.01 * p[i];
        for (int j = 1; j < t[i]; j++) {
            c *= (1 - pr);
        }
        for (int j = 0; j <= T; j++) {
            dp[0][j]++;
        }
        for (int j = 1; j <= T; j++) {
            if (j - 1 >= t[i]) {
                v -= dp[0][j - 1 - t[i]] * c;
            }
            v *= (1 - pr);
            if (j >= t[i]) {
                v += c * (1 - pr) * dp[0][j - t[i]];
            }
            v += dp[0][j - 1] * pr;
            dp[1][j] = v;
        }
        std::swap(dp[0], dp[1]);
    }
    std::cout << std::fixed << std::setprecision(10) << dp[0][T] << "\n";
    return 0;
}
