// url:https://codeforces.com/contest/44/problem/H
// time:2023-04-23 12:35:20
// name:H-PhoneNumber

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s;
    std::cin >> s;
    
    int n = s.size();
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = s[i] - '0';
    }
    
    std::array<i64, 10> dp{};
    dp.fill(1);
    for (int i = 1; i < n; i++) {
        std::array<i64, 10> g{};
        for (int x = 0; x < 10; x++) {
            g[(x + a[i]) / 2] += dp[x];
            if ((x + a[i]) % 2 == 1) {
                g[(x + a[i]) / 2 + 1] += dp[x];
            }
        }
        dp = g;
    }
    auto ans = std::accumulate(dp.begin(), dp.end(), 0LL);
    
    bool ok = true;
    for (int i = 1; i < n; i++) {
        if (std::abs(a[i] - a[i-1]) > 1) {
            ok = false;
        }
    }
    ans -= ok;
    
    std::cout << ans << "\n";
    
    return 0;
}
