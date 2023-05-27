// url:https://codeforces.com/contest/1807/problem/F
// time:2023-03-20 16:08:25
// name:F-BouncyBall

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m, i1, j1, i2, j2;
    std::string d;
    std::cin >> n >> m >> i1 >> j1 >> i2 >> j2 >> d;
    
    int dx = 1;
    int dy = 1;
    if (d[0] == 'U') {
        dx = -1;
    }
    if (d[1] == 'L') {
        dy = -1;
    }
    
    int cnt = 0;
    int ans = 0;
    while (cnt < 4 * n * m) {
        if (i1 == i2 && j1 == j2) {
            std::cout << ans << "\n";
            return;
        }
        cnt++;
        bool bounce = false;
        if (i1 + dx < 1 || i1 + dx > n) {
            bounce = true;
            dx *= -1;
        }
        if (j1 + dy < 1 || j1 + dy > m) {
            bounce = true;
            dy *= -1;
        }
        ans += bounce;
        i1 += dx;
        j1 += dy;
    }
    std::cout << -1 << "\n";
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
