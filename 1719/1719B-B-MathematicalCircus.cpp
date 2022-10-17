//url:https://codeforces.com/contest/1719/problem/B
//time:2022-09-29 14:39:30
//name:B-MathematicalCircus

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    if (k % 2 == 1) {
        std::cout << "YES\n";
        for (int i = 1; i <= n; i += 2) {
            std::cout << i << " " << i + 1 << "\n";
        }
    } else if (k % 4 == 2) {
        std::cout << "YES\n";
        for (int i = 1; i <= n; i += 2) {
            if (i % 4 == 1) {
                std::cout << i + 1 << " " << i << "\n";
            } else {
                std::cout << i << " " << i + 1 << "\n";
            }
        }
    } else {
        std::cout << "NO\n";
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
