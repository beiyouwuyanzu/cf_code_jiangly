// url:https://codeforces.com/contest/1616/problem/D
// time:2021-12-29 18:48:44
// name:D-KeeptheAverageHigh

#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    int x;
    std::cin >> x;
    
    int ans = 0;
    for (int i = 0, j = 0; i < n; i++) {
        bool nice = true;
        if (i - j >= 1 && a[i - 1] + a[i] < 2 * x) {
            nice = false;
        }
        if (i - j >= 2 && a[i - 2] + a[i - 1] + a[i] < 3 * x) {
            nice = false;
        }
        if (!nice) {
            ans++;
            j = i + 1;
        }
    }
    
    std::cout << n - ans << "\n";
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

