//url:https://codeforces.com/contest/1728/problem/B
//time:2022-09-08 17:41:32
//name:B-BestPermutation

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    if (n % 2 == 0) {
        for (int i = n - 2; i >= 1; i--) {
            std::cout << i << " ";
        }
        std::cout << n - 1 << " " << n << "\n";
    } else {
        for (int i = n - 2; i >= 4; i--) {
            std::cout << i << " ";
        }
        std::cout << 1 << " " << 2 << " " << 3 << " " << n - 1 << " " << n << "\n";
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
