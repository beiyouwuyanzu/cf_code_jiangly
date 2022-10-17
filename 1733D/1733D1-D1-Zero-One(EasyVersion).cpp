//url:https://codeforces.com/contest/1733/problem/D1
//time:2022-09-19 17:54:11
//name:D1-Zero-One(EasyVersion)

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, x, y;
    std::cin >> n >> x >> y;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        char ch;
        std::cin >> ch;
        a[i] ^= ch - '0';
    }
    for (int i = 0; i < n; i++) {
        char ch;
        std::cin >> ch;
        a[i] ^= ch - '0';
    }
    
    int cnt = std::accumulate(a.begin(), a.end(), 0);
    if (cnt % 2 != 0) {
        std::cout << -1 << "\n";
        return;
    }
    std::vector<int> pos;
    
    for (int i = 0; i < n; i++) {
        if (a[i]) {
            pos.push_back(i);
        }
    }
    
    if (x >= y) {
        if (cnt != 2 || pos[1] > pos[0] + 1) {
            std::cout << 1LL * (cnt / 2) * y << "\n";
            return;
        }
        int ans = x;
        if (pos[0] > 1 || pos[1] < n - 2) {
            ans = std::min(ans, 2 * y);
        } else if (n >= 4) {
            ans = std::min(1LL * ans, 3LL * y);
        }
        std::cout << ans << "\n";
        return;
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
