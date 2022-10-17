//url:https://codeforces.com/contest/1733/problem/C
//time:2022-09-19 17:46:19
//name:C-ParityShuffleSorting

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<std::array<int, 2>> ans;
    if (n > 1 && a[n - 1] % 2 == a[0] % 2) {
        ans.push_back({0, n - 1});
        a[0] = a[n - 1];
    }
    for (int i = 1; i < n; i++) {
        if (a[i] % 2 != a[0] % 2) {
            ans.push_back({0, i});
            a[i] = a[0];
        }
    }
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] != a[n - 1]) {
            ans.push_back({i, n - 1});
            a[i] = a[n - 1];
        }
    }
    
    std::cout << ans.size() << "\n";
    for (auto [l, r] : ans) {
        std::cout << l + 1 << " " << r + 1 << "\n";
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
