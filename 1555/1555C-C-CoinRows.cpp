//url:https://codeforces.com/contest/1555/problem/C
//time:2022-06-12 10:25:10
//name:C-CoinRows

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int m;
    std::cin >> m;
    
    std::vector a(2, std::vector<int>(m));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
    
    i64 L = 0;
    i64 R = std::accumulate(a[0].begin(), a[0].end(), 0LL);
    i64 ans = R;
    for (int i = 0; i < m; i++) {
        R -= a[0][i];
        ans = std::min(ans, std::max(L, R));
        L += a[1][i];
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

