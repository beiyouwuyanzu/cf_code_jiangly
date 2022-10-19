// url:https://codeforces.com/contest/1638/problem/D
// time:2022-02-14 19:09:26
// name:D-BigBrush

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
        }
    }
    
    std::vector<std::array<int, 3>> ans;
    
    auto check = [&](auto self, int i, int j) -> void {
        if (i < 0 || i >= n - 1 || j < 0 || j >= m - 1) {
            return;
        }
        int c = -1;
        for (auto x : {i, i + 1}) {
            for (auto y : {j, j + 1}) {
                if (a[x][y] != -1) {
                    if (c != -1 && c != a[x][y]) {
                        return;
                    }
                    c = a[x][y];
                }
            }
        }
        if (c != -1) {
            ans.push_back({i, j, c});
            for (auto x : {i, i + 1}) {
                for (auto y : {j, j + 1}) {
                    a[x][y] = -1;
                }
            }
            for (auto x : {i - 1, i, i + 1}) {
                for (auto y : {j - 1, j, j + 1}) {
                    self(self, x, y);
                }
            }
        }
    };
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m - 1; j++) {
            check(check, i, j);
        }
    }
    
    if (a != std::vector(n, std::vector(m, -1))) {
        std::cout << "-1\n";
        return 0;
    }
    
    std::reverse(ans.begin(), ans.end());
    
    std::cout << ans.size() << "\n";
    for (auto [i, j, c] : ans) {
        std::cout << i + 1 << " " << j + 1 << " " << c << "\n";
    }
    
    return 0;
}
