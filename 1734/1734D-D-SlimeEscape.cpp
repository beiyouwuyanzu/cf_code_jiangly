//url:https://codeforces.com/contest/1734/problem/D
//time:2022-09-23 15:44:37
//name:D-SlimeEscape

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    k--;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<std::array<i64, 2>> l, r;
    for (int i = 0; i < k; i++) {
        l.push_back({std::min(a[i], 0), a[i]});
        while (l.size() > 1 && l.back()[1] <= 0) {
            auto [x, y] = l.back();
            l.pop_back();
            l.back() = {std::min(x, y + l.back()[0]), y + l.back()[1]};
        }
    }
    for (int i = n - 1; i > k; i--) {
        r.push_back({std::min(a[i], 0), a[i]});
        while (r.size() > 1 && r.back()[1] <= 0) {
            auto [x, y] = r.back();
            r.pop_back();
            r.back() = {std::min(x, y + r.back()[0]), y + r.back()[1]};
        }
    }
    
    i64 cur = a[k];
    while (!l.empty() && !r.empty()) {
        if (cur + l.back()[0] >= 0) {
            cur += l.back()[1];
            l.pop_back();
        } else if (cur + r.back()[0] >= 0) {
            cur += r.back()[1];
            r.pop_back();
        } else {
            std::cout << "NO\n";
            return;
        }
    }
    
    std::cout << "YES\n";
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
