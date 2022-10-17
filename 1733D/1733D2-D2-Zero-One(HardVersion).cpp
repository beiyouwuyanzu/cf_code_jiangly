//url:https://codeforces.com/contest/1733/problem/D2
//time:2022-09-19 17:59:22
//name:D2-Zero-One(HardVersion)

#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 inf = 1E18;

void solve() {
    int n, x, y;
    std::cin >> n >> x >> y;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        char ch;
        std::cin >> ch;
        a[i] ^= ch - '0';
    }
    for (int i = 0; i < n; i++) {
        char ch;
        std::cin >> ch;
        a[i] ^= ch - '0';
    }
    
    int cnt = std::accumulate(a.begin(), a.end(), 0);
    if (cnt % 2 != 0) {
        std::cout << -1 << "\n";
        return;
    }
    std::vector<int> pos;
    
    for (int i = 0; i < n; i++) {
        if (a[i]) {
            pos.push_back(i);
        }
    }
    
    if (x >= y) {
        if (cnt != 2 || pos[1] > pos[0] + 1) {
            std::cout << 1LL * (cnt / 2) * y << "\n";
            return;
        }
        int ans = x;
        if (pos[0] > 1 || pos[1] < n - 2) {
            ans = std::min(ans, 2 * y);
        } else if (n >= 4) {
            ans = std::min(1LL * ans, 3LL * y);
        }
        std::cout << ans << "\n";
        return;
    }
    
    const int N = pos.size();
    std::vector<i64> dp(N + 1, inf);
    dp[0] = 0;
    for (int i = 0; i < N; i += 2) {
        i64 cur = 0;
        for (int j = i + 2; j <= N; j += 2) {
            if (j >= i + 4) {
                cur += 1LL * x * (pos[j - 2] - pos[j - 3]);
            }
            dp[j] = std::min(dp[j], dp[i] + std::min(1LL * y, 1LL * x * (pos[j - 1] - pos[i])) + cur);
        }
    }
    std::cout << dp[N] << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
