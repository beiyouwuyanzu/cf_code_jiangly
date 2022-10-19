// url:https://codeforces.com/contest/1680/problem/B
// time:2022-05-16 16:44:26
// name:B-Robots

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::string> s(n);
    int r = n, c = m;
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'R') {
                r = std::min(r, i);
                c = std::min(c, j);
            }
        }
    }
    
    if (s[r][c] == 'R') {
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
