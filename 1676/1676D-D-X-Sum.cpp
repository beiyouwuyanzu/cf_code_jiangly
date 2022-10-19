// url:https://codeforces.com/contest/1676/problem/D
// time:2022-05-10 17:52:52
// name:D-X-Sum

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector a(n, std::vector<int>(m)), f(a), g(a);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
            f[i][j] = g[i][j] = a[i][j];
            if (i > 0 && j > 0) {
                f[i][j] += f[i - 1][j - 1];
            }
            if (i > 0 && j + 1 < m) {
                g[i][j] += g[i - 1][j + 1];
            }
        }
    }
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < m; j++) {
            if (j > 0) {
                f[i - 1][j - 1] = f[i][j];
            }
            if (j + 1 < m) {
                g[i - 1][j + 1] = g[i][j];
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans = std::max(ans, f[i][j] + g[i][j] - a[i][j]);
        }
    }
    std::cout << ans << "\n";
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
