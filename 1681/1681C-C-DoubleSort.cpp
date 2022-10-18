//url:https://codeforces.com/contest/1681/problem/C
//time:2022-05-23 17:46:05
//name:C-DoubleSort

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<int> b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    
    std::vector<std::array<int, 2>> ans;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i] < a[j] || (a[i] == a[j] && b[i] < b[j])) {
                ans.push_back({i, j});
                std::swap(a[i], a[j]);
                std::swap(b[i], b[j]);
            }
        }
    }
    
    assert(std::is_sorted(a.begin(), a.end()));
    if (std::is_sorted(b.begin(), b.end())) {
        std::cout << ans.size() << "\n";
        for (auto [x, y] : ans) {
            std::cout << x + 1 << " " << y + 1 << "\n";
        }
    } else {
        std::cout << "-1\n";
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
