// url:https://codeforces.com/contest/707/problem/C
// time:2023-03-15 09:14:14
// name:C-PythagoreanTriples

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    if (n <= 2) {
        std::cout << -1 << "\n";
        return 0;
    }
    
    int k = __builtin_ctz(n);
    int m = n >> k;
    
    if (m == 1) {
        std::cout << n / 4 * 3 << " " << n / 4 * 5 << "\n";
        return 0;
    }
    
    std::cout << (1LL * m * m / 2) * (1 << k) << " " << (1LL * m * m / 2 + 1) * (1 << k) << "\n";
    
    return 0;
}

