// url:https://codeforces.com/contest/1822/problem/D
// time:2023-04-25 15:33:07
// name:D-Super-Permutation

#include <bits/stdc++.h> 

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    if (n == 1) {
        std::cout << 1 << "\n";
    } else if (n % 2 == 1) {
        std::cout << -1 << "\n";
    } else {
        for (int i = 0; i < n; i++) {
            int x = i % 2 ? n - i : i;
            if (!i) {
                x = n;
            }
            std::cout << x << " \n"[i == n-1];
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
