// url:https://codeforces.com/contest/1741/problem/F
// time:2022-10-11 18:07:06
// name:F-Multi-ColoredSegments

#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1E9;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<std::array<int, 5>> pts(2 * n);
    for (int i = 0; i < n; i++) {
        int l, r, c;
        std::cin >> l >> r >> c;
        pts[2 * i] = {l, r, c, i, 0};
        pts[2 * i + 1] = {r, l, c, i, 1};
    }
    
    std::sort(pts.begin(), pts.end());
    
    std::vector<int> ans(n, inf);
    
    for (int t = 0; t < 2; t++) {
        std::array<int, 2> f[2];
        f[0] = f[1] = {-inf, -1};
        for (auto [x, y, c, i, o] : pts) {
            if (!o) {
                std::array g{y, c};
                if (g > f[0]) {
                    std::swap(g, f[0]);
                }
                if ((g > f[1] && g[1] != f[0][1]) || f[0][1] == f[1][1]) {
                    f[1] = g;
                }
            } else {
                for (auto [z, d] : f) {
                    if (d != c) {
                        ans[i] = std::min(ans[i], std::max(0, y - z));
                    }
                }
            }
        }
        std::reverse(pts.begin(), pts.end());
        for (auto &[x, y, c, i, o] : pts) {
            x = inf - x;
            y = inf - y;
            o ^= 1;
        }
    }
    
    for (int i = 0; i < n; i++) {
        std::cout << ans[i] << " \n"[i == n - 1];
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

