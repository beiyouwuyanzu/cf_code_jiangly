//url:https://codeforces.com/contest/1623/problem/A
//time:2021-12-28 17:41:56
//name:A-RobotCleaner

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m, rb, cb, rd, cd;
    std::cin >> n >> m >> rb >> cb >> rd >> cd;
    rb--;
    cb--;
    rd--;
    cd--;
    
    int ans = std::min({
        rb <= rd ? rd - rb : 2 * (n - 1) - rb - rd,
        cb <= cd ? cd - cb : 2 * (m - 1) - cb - cd
    });
    
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

