// url:https://codeforces.com/contest/1635/problem/B
// time:2022-02-20 18:07:05
// name:B-AvoidLocalMaximums

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    int ans = 0;
    for (int i = 2; i < n - 2; i++) {
        if (a[i - 1] > a[i - 2] && a[i - 1] > a[i] && a[i + 1] > a[i] && a[i + 1] > a[i + 2]) {
            ans++;
            a[i] = std::max(a[i - 1], a[i + 1]);
        }
    }
    for (int i = 1; i < n - 1; i++) {
        if (a[i] > a[i - 1] && a[i] > a[i + 1]) {
            ans++;
            a[i] = std::max(a[i - 1], a[i + 1]);
        }
    }
    
    std::cout << ans << "\n";
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " \n"[i == n - 1];
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
