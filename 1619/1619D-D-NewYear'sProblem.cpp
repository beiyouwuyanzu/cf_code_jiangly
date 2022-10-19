// url:https://codeforces.com/contest/1619/problem/D
// time:2021-12-20 18:08:00
// name:D-NewYear'sProblem

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> m >> n;
    
    std::vector p(n, std::vector<int>(m));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> p[j][i];
        }
    }
    
    int l = 0, r = 1E9;
    for (int i = 0; i < n; i++) {
        r = std::min(r, *std::max_element(p[i].begin(), p[i].end()));
    }
    while (l < r) {
        int x = (l + r + 1) / 2;
        
        std::vector<bool> v(m);
        bool nice = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (p[i][j] >= x) {
                    if (v[j]) {
                        nice = true;
                    }
                    v[j] = true;
                }
            }
        }
        
        if (nice) {
            l = x;
        } else {
            r = x - 1;
        }
    }
    
    std::cout << l << "\n";
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

