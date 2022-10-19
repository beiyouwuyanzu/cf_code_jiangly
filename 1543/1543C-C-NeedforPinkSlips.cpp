// url:https://codeforces.com/contest/1543/problem/C
// time:2021-07-07 17:55:16
// name:C-NeedforPinkSlips

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::cout << std::fixed << std::setprecision(10);
    
    int t;
    std::cin >> t;
    while (t--) {
        
        double c, m, p, fv;
        std::cin >> c >> m >> p >> fv;
        
        int v = 40000 * fv + 0.5;
        
        auto solve = [&](auto self, int c, int m, int p) -> double {
            double ans = 1;
            if (c > 0) {
                int x = std::min(v, c);
                if (m == 0) {
                    ans += c / 40000.0 * self(self, c - x, 0, p + x);
                } else {
                    ans += c / 40000.0 * self(self, c - x, m + x / 2, p + x / 2);
                }
            }
            if (m > 0) {
                int x = std::min(v, m);
                if (c == 0) {
                    ans += m / 40000.0 * self(self, 0, m - x, p + x);
                } else {
                    ans += m / 40000.0 * self(self, c + x / 2, m - x, p + x / 2);
                }
            }
            return ans;
        };
        
        std::cout << solve(solve, int(c * 40000 + 0.5), int(m * 40000 + 0.5), int(p * 40000 + 0.5)) << "\n";
    }
    
    return 0;
}
