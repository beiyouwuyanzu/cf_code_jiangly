//url:https://codeforces.com/contest/1700/problem/E
//time:2022-06-19 14:26:58
//name:E-SeregathePirate

#include <bits/stdc++.h>
 
using i64 = long long;
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector a(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
            a[i][j]--;
        }
    }
    
    auto isGood = [&](int x, int y) {
        if (a[x][y] == 0) {
            return true;
        }
        if (x > 0 && a[x - 1][y] < a[x][y]) {
            return true;
        }
        if (x < n - 1 && a[x + 1][y] < a[x][y]) {
            return true;
        }
        if (y > 0 && a[x][y - 1] < a[x][y]) {
            return true;
        }
        if (y < m - 1 && a[x][y + 1] < a[x][y]) {
            return true;
        }
        return false;
    };
    
    auto neighbor = [&](int x0, int y0) {
        std::set<std::array<int, 2>> a;
        for (auto [dx, dy] : {std::array{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}}) {
            int x = x0 + dx;
            int y = y0 + dy;
            if (x >= 0 && x < n && y >= 0 && y < m) {
                a.insert({x, y});
            }
        }
        return a;
    };
    
    std::vector<std::array<int, 2>> bad;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!isGood(i, j)) {
                bad.push_back({i, j});
            }
        }
    }
    
    if (bad.empty()) {
        std::cout << "0\n";
        return 0;
    }
    
    if (bad.size() > 5) {
        std::cout << "2\n";
        return 0;
    }
    
    std::set<std::array<std::array<int, 2>, 2>> s;
    for (auto [x0, y0] : bad) {
        for (auto [x, y] : neighbor(x0, y0)) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    bool good = true;
                    for (auto [u, v] : bad) {
                        if (std::abs(u - x) + std::abs(v - y) > 1 && std::abs(u - i) + std::abs(v - j) > 1) {
                            good = false;
                        }
                    }
                    std::swap(a[i][j], a[x][y]);
                    for (auto [x0, y0] : {std::array{i, j}, {x, y}}) {
                        for (auto [x, y] : neighbor(x0, y0)) {
                            if (!isGood(x, y)) {
                                good = false;
                            }
                        }
                    }
                    std::swap(a[i][j], a[x][y]);
                    if (good) {
                        if (std::array{x, y} < std::array{i, j}) {
                            s.insert({{{x, y}, {i, j}}});
                        } else {
                            s.insert({{{i, j}, {x, y}}});
                        }
                    }
                }
            }
        }
        break;
    }
    
    if (!s.empty()) {
        std::cout << "1 " << s.size() << "\n";
    } else {
        std::cout << "2\n";
    }
    
    return 0;
}
