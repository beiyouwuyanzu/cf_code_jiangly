//url:https://codeforces.com/contest/1622/problem/E
//time:2022-06-09 16:15:22
//name:E-MathTest

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> x(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i];
    }
    
    std::vector<std::string> s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }
    
    int ans = 0;
    std::vector<int> p(m);
    for (int mask = 0; mask < (1 << n); mask++) {
        int res = 0;
        std::vector<std::array<int, 2>> coef(m);
        for (int i = 0; i < m; i++) {
            coef[i][1] = i;
        }
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                res -= x[i];
                for (int j = 0; j < m; j++) {
                    if (s[i][j] == '1') {
                        coef[j][0]++;
                    }
                }
            } else {
                res += x[i];
                for (int j = 0; j < m; j++) {
                    if (s[i][j] == '1') {
                        coef[j][0]--;
                    }
                }   
            }
        }
        std::sort(coef.begin(), coef.end());
        for (int i = 0; i < m; i++) {
            res += coef[i][0] * (i + 1);
        }
        
        if (res >= ans) {
            ans = res;
            for (int i = 0; i < m; i++) {
                p[coef[i][1]] = i + 1;
            }
        }
    }
    
    for (int i = 0; i < m; i++) {
        std::cout << p[i] << " \n"[i == m - 1];
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
