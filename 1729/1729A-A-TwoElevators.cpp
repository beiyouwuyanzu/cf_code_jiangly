//url:https://codeforces.com/contest/1729/problem/A
//time:2022-09-12 17:36:39
//name:A-TwoElevators

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int a, b, c;
    std::cin >> a >> b >> c;
    a--;
    b = std::abs(b - c) + c - 1;
    std::cout << (a < b ? 1 : a > b ? 2 : 3) << "\n";
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
