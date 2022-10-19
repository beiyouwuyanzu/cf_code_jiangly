// url:https://codeforces.com/contest/506/problem/A
// time:2021-06-24 16:59:25
// name:A-Mr.Kitayuta,theTreasureHunter

#include <bits/stdc++.h>
using i64 = long long;
constexpr int C = 30001;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, d;
    std::cin >> n >> d;
    int lo = std::max(d - 250, 1);
    int hi = d + 250;
    std::vector<int> v(C);
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        v[x]++;
    }
    std::vector<std::vector<int>> dp(C, std::vector<int>(hi - lo, -1));
    dp[d][d - lo] = v[d];
    int ans = 0;
    for (int i = d; i < C; i++) {
        for (int j = lo; j < hi; j++) {
            if (dp[i][j - lo] < 0) {
                continue;
            }
            ans = std::max(ans, dp[i][j - lo]);
            for (int x : {j - 1, j, j + 1}) {
                if (x < lo || x >= hi || i + x >= C) {
                    continue;
                }
                dp[i + x][x - lo] = std::max(dp[i + x][x - lo], dp[i][j - lo] + v[i + x]);
            }
        }
    }
    std::cout << ans << "\n";
    return 0;
}
