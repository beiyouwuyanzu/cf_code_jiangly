// url:https://codeforces.com/contest/1806/problem/A
// time:2023-03-20 20:49:18
// name:A-WalkingMaster

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    
    a -= b;
    c -= d;
    
    if (a < c || b > d) {
        std::cout << -1 << "\n";
        return;
    }
    
    int ans = (a - c) + (d - b);
    std::cout << ans << "\n";
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
