//url:https://codeforces.com/contest/1739/problem/B
//time:2022-09-29 17:55:29
//name:B-ArrayRecovery

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> d(n);
    for (int i = 0; i < n; i++) {
        std::cin >> d[i];
    }
    
    std::vector<int> a(n);
    a[0] = d[0];
    for (int i = 1; i < n; i++) {
        if (d[i] > 0 && a[i - 1] >= d[i]) {
            std::cout << -1 << "\n";
            return;
        }
        a[i] = a[i - 1] + d[i];
    }
    
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " \n"[i == n - 1];
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
