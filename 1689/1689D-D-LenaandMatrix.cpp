//url:https://codeforces.com/contest/1689/problem/D
//time:2022-06-10 20:01:56
//name:D-LenaandMatrix

#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1E9;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::string> s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }
    
    int l = 0, r = n + m;
    int a = 0, b = 0;
    
    while (l < r) {
        int k = (l + r) / 2;
        
        int pp = inf, pm = inf, mp = inf, mm = inf;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (s[i][j] == 'B') {
                    pp = std::min(pp, i + j + k);
                    pm = std::min(pm, i - j + k);
                    mp = std::min(mp, -i + j + k);
                    mm = std::min(mm, -i - j + k);
                }
            }
        }
        
        int x = (pp + pm) >> 1;
        int y = std::min(pp - x, mp + x);
        
        if (-x - y <= mm && x - y <= pm) {
            r = k;
            a = x;
            b = y;
        } else {
            l = k + 1;
        }
    }
    
    a = std::max(0, std::min(n - 1, a));
    b = std::max(0, std::min(m - 1, b));
    std::cout << a + 1 << " " << b + 1 << "\n";
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

