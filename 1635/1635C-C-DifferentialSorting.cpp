// url:https://codeforces.com/contest/1635/problem/C
// time:2022-02-20 18:13:08
// name:C-DifferentialSorting

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<i64> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    if (std::is_sorted(a.begin(), a.end())) {
        std::cout << "0\n";
        return;
    }
    
    if (a[n - 2] > a[n - 1] || a[n - 1] < 0) {
        std::cout << "-1\n";
        return;
    }
    
    std::cout << n - 2 << "\n";
    for (int i = n - 3; i >= 0; i--) {
        std::cout << i + 1 << " " << i + 2 << " " << n << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        solve();
    }
    
    return 0;
}
