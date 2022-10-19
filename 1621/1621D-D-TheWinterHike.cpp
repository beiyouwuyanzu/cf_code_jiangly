// url:https://codeforces.com/contest/1621/problem/D
// time:2022-01-04 11:22:20
// name:D-TheWinterHike

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector c(2 * n, std::vector<int>(2 * n));
    i64 ans = 0;
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            std::cin >> c[i][j];
            if (i >= n && j >= n) {
                ans += c[i][j];
                c[i][j] = 0;
            }
        }
    }
    
    ans += std::min({c[0][n], c[0][2 * n - 1], c[n - 1][n], c[n - 1][2 * n - 1], c[n][0], c[n][n - 1], c[2 * n - 1][0], c[2 * n - 1][n - 1]});
    
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

