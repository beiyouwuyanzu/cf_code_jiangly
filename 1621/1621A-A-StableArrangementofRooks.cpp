// url:https://codeforces.com/contest/1621/problem/A
// time:2022-01-03 17:37:31
// name:A-StableArrangementofRooks

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    if (n < 2 * k - 1) {
        std::cout << "-1\n";
    } else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j && i % 2 == 0 && i < 2 * k) {
                    std::cout << "R";
                } else {
                    std::cout << ".";
                }
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

