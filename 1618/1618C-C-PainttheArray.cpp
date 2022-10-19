// url:https://codeforces.com/contest/1618/problem/C
// time:2021-12-22 10:21:39
// name:C-PainttheArray

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<i64> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    for (int c : {0, 1}) {
        i64 g = 0;
        for (int i = c; i < n; i += 2) {
            g = std::gcd(g, a[i]);
        }
        bool nice = true;
        for (int i = !c; i < n; i += 2) {
            if (a[i] % g == 0) {
                nice = false;
            }
        }
        if (nice) {
            std::cout << g << "\n";
            return;
        }
    }
    std::cout << "0\n";
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
