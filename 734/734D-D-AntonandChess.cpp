// url:https://codeforces.com/contest/734/problem/D
// time:2021-12-23 19:05:08
// name:D-AntonandChess

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    int x0, y0;
    std::cin >> x0 >> y0;
    
    std::vector<int> x(n), y(n);
    std::vector<char> t(n);
    for (int i = 0; i < n; i++) {
        std::cin >> t[i] >> x[i] >> y[i];
    }
    
    for (auto move : {std::pair(-1, -1), {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}) {
        int j = -1;
        i64 d = 1E18;
        
        i64 v = std::abs(move.first) + std::abs(move.second);
        for (int i = 0; i < n; i++) {
            i64 id = 1LL * std::abs(x0 - x[i]) + std::abs(y0 - y[i]);
            if (x[i] == x0 + id / v * move.first && y[i] == y0 + id / v * move.second && id < d) {
                d = id;
                j = i;
            }
        }
        
        if (j != -1 && (t[j] == 'Q' || t[j] == (v == 1 ? 'R' : 'B'))) {
            std::cout << "YES\n";
            return 0;
        }
    }
    
    std::cout << "NO\n";
    
    return 0;
}
