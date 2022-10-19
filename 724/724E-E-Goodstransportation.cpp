// url:https://codeforces.com/contest/724/problem/E
// time:2021-12-23 17:49:44
// name:E-Goodstransportation

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, c;
    std::cin >> n >> c;
    
    std::vector<int> p(n), s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }
    
    std::vector<i64> dp(n + 1, 1E18);
    
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j >= 0; j--) {
            dp[j + 1] = std::min(dp[j + 1], dp[j] + s[i]);
            dp[j] += p[i] + 1LL * j * c;
        }
    }
    
    std::cout << *std::min_element(dp.begin(), dp.end()) << "\n";
    
    return 0;
}
