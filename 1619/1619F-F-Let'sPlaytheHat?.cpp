// url:https://codeforces.com/contest/1619/problem/F
// time:2021-12-20 18:16:56
// name:F-Let'sPlaytheHat?

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;
    
    for (int i = 0; i < k; i++) {
        int v = n % m * ((n + m - 1) / m) * i % n;
        
        for (int j = 0; j < n % m; j++) {
            std::cout << (n + m - 1) / m;
            for (int l = 0; l < (n + m - 1) / m; l++) {
                std::cout << " " << v + 1;
                v = (v + 1) % n;
            }
            std::cout << "\n";
        }
        for (int j = 0; j < m - n % m; j++) {
            std::cout << n / m;
            for (int l = 0; l < n / m; l++) {
                std::cout << " " << v + 1;
                v = (v + 1) % n;
            }
            std::cout << "\n";
        }
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

