// url:https://codeforces.com/contest/1620/problem/D
// time:2021-12-18 20:02:40
// name:D-ExactChange

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    int ans = 1E9;
    for (int x = 0; x <= 2; x++) {
        for (int y = 0; y <= 2; y++) {
            int res = 0;
            for (int i = 0; i < n; i++) {
                int mn = 1E9;
                for (int sx = 0; sx <= x; sx++) {
                    for (int sy = 0; sy <= y; sy++) {
                        int v = a[i] - sx - 2 * sy;
                        if (v >= 0 && v % 3 == 0) {
                            mn = std::min(mn, v / 3);
                        }
                    }
                }
                res = std::max(res, mn);
            }
            ans = std::min(ans, res + x + y);
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

