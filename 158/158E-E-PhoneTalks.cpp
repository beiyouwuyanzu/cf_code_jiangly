// url:https://codeforces.com/contest/158/problem/E
// time:2023-04-26 20:12:58
// name:E-PhoneTalks

#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 86400;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> t(n), d(n);
    for (int i = 0; i < n; i++) {
        std::cin >> t[i] >> d[i];
    }
    
    int ans = n ? t[0] - 1 : N;
    std::vector<int> dp(k+1);
    for (int i = 0; i < n; i++) {
        for (int j = k; j >= 0; j--) {
            if (j < k) {
                dp[j+1] = std::min(dp[j+1], dp[j]);
            }
            dp[j] = std::max(dp[j]+1, t[i]) + d[i] - 1;
        }
        ans = std::max(ans, (i < n-1 ? t[i+1]-1 : N) - dp[k]);
    }
    std::cout << ans << "\n";
    
    return 0;
}
