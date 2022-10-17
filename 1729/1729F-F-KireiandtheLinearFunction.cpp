//url:https://codeforces.com/contest/1729/problem/F
//time:2022-09-12 17:56:42
//name:F-KireiandtheLinearFunction

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s;
    std::cin >> s;
    
    int n = s.length();
    
    int w, m;
    std::cin >> w >> m;
    
    std::vector<int> f(n + 1);
    for (int i = 0; i < n; i++) {
        f[i + 1] = f[i] + s[i] - '0';
    }
    
    std::vector<int> a[9];
    for (int i = 0; i + w <= n; i++) {
        int x = (f[i + w] - f[i]) % 9;
        a[x].push_back(i);
    }
    
    for (int i = 0; i < m; i++) {
        int l, r, k;
        std::cin >> l >> r >> k;
        
        int x = (f[r] - f[l - 1]) % 9;
        std::array<int, 2> ans{n, n};
        for (int u = 0; u < 9; u++) {
            if (a[u].size() > 1 && (u * x + u) % 9 == k) {
                ans = std::min(ans, std::array{a[u][0], a[u][1]});
            }
            for (int v = 0; v < 9; v++) {
                if (u != v && !a[u].empty() && !a[v].empty() && (u * x + v) % 9 == k) {
                    ans = std::min(ans, std::array{a[u][0], a[v][0]});
                }
            }
        }
        
        if (ans[0] == n) {
            std::cout << -1 << " " << -1 << "\n";
        } else {
            std::cout << ans[0] + 1 << " " << ans[1] + 1 << "\n";
        }
    }
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
