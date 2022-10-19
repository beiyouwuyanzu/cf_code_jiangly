// url:https://codeforces.com/contest/1620/problem/B
// time:2021-12-18 20:15:40
// name:B-TrianglesonaRectangle

#include <bits/stdc++.h>

using i64 = long long;

std::pair<int, int> get() {
    int k;
    std::cin >> k;
    int x1, x2;
    for (int i = 0; i < k; i++) {
        int x;
        std::cin >> x;
        if (i == 0) {
            x1 = x;
        }
        if (i == k - 1) {
            x2 = x;
        }
    }
    return {x1, x2};
}

i64 area(std::pair<int, int> a, std::pair<int, int> b, std::pair<int, int> c) {
    return std::abs(1LL * (b.first - a.first) * (c.second - a.second) - 1LL * (b.second - a.second) * (c.first - a.first));
}

void solve() {
    int w, h;
    std::cin >> w >> h;
    
    std::vector<std::vector<std::pair<int, int>>> v(4);
    
    auto [x1, x2] = get();
    v[0] = {{x1, 0}, {x2, 0}};
    auto [x3, x4] = get();
    v[1] = {{x3, h}, {x4, h}};
    auto [y1, y2] = get();
    v[2] = {{0, y1}, {0, y2}};
    auto [y3, y4] = get();
    v[3] = {{w, y3}, {w, y4}};
    
    i64 ans = 0;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i != j) {
                for (int k = 0; k < 2; k++) {
                    ans = std::max(ans, area(v[i][0], v[i][1], v[j][k]));
                }
            }
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

