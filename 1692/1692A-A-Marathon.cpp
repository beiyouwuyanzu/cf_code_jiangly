//url:https://codeforces.com/contest/1692/problem/A
//time:2022-06-14 17:36:16
//name:A-Marathon

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    
    std::cout << (b > a) + (c > a) + (d > a) << "\n";
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

