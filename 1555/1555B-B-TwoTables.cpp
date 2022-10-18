//url:https://codeforces.com/contest/1555/problem/B
//time:2022-06-12 10:22:27
//name:B-TwoTables

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int W, H;
    std::cin >> W >> H;
    
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    
    int w, h;
    std::cin >> w >> h;
    
    int ans = W + H;
    if (x2 - x1 + w <= W) {
        if (x1 >= w || x2 + w <= W) {
            ans = 0;
        } else {
            ans = std::min({ ans, w - x1, x2 - (W - w) });
        }
    }
    if (y2 - y1 + h <= H) {
        if (y1 >= h || y2 + h <= H) {
            ans = 0;
        } else {
            ans = std::min({ ans, h - y1, y2 - (H - h) });
        }
    }
    if (ans == W + H) {
        ans = -1;
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

