// url:https://codeforces.com/contest/1525/problem/A
// time:2022-03-01 14:29:07
// name:A-Potion-making

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int k;
    std::cin >> k;
    
    std::cout << 100 / std::gcd(100, k) << "\n";
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
