// url:https://codeforces.com/contest/1676/problem/C
// time:2022-05-10 17:49:54
// name:C-MostSimilarWords

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::string> s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }
    
    int ans = 1E9;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int res = 0;
            for (int k = 0; k < m; k++) {
                int x = std::abs(s[i][k] - s[j][k]);
                res += x;
            }
            ans = std::min(ans, res);
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
