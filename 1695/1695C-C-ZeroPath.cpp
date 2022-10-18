//url:https://codeforces.com/contest/1695/problem/C
//time:2022-06-18 17:49:01
//name:C-ZeroPath

#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1E9;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector a(n, std::vector(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
    
    if ((n + m - 1) % 2 != 0) {
        std::cout << "NO\n";
        return;
    }
    
    std::vector min(n, std::vector(m, inf)), max(n, std::vector(m, -inf));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                min[i][j] = max[i][j] = 0;
            } else if (i == 0) {
                min[i][j] = min[i][j - 1];
                max[i][j] = max[i][j - 1];
            } else if (j == 0) {
                min[i][j] = min[i - 1][j];
                max[i][j] = max[i - 1][j];
            } else {
                min[i][j] = std::min(min[i - 1][j], min[i][j - 1]);
                max[i][j] = std::max(max[i - 1][j], max[i][j - 1]);
            }
            min[i][j] += a[i][j];
            max[i][j] += a[i][j];
        }
    }
    
    if (min[n - 1][m - 1] <= 0 && max[n - 1][m - 1] >= 0) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
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

