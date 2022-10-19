// url:https://codeforces.com/contest/1508/problem/B
// time:2021-04-16 17:51:58
// name:B-AlmostSorted

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
constexpr i64 inf = 1e18;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        i64 k;
        std::cin >> n >> k;
        k--;
        std::vector<i64> dp(n + 1);
        dp[0] = dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = std::min(inf, dp[i - 1] * 2);
        }
        if (k >= dp[n]) {
            std::cout << "-1\n";
            continue;
        }
        int x = 0;
        std::vector<int> ans(n);
        std::iota(ans.begin(), ans.end(), 0);
        while (x < n) {
            int y = 1;
            while (k >= dp[n - x - y]) {
                k -= dp[n - x - y];
                y++;
            }
            std::reverse(ans.begin() + x, ans.begin() + x + y);
            x += y;
        }
        for (int i = 0; i < n; i++) {
            std::cout << ans[i] + 1 << " \n"[i == n - 1];
        }
    }
    return 0;
}
