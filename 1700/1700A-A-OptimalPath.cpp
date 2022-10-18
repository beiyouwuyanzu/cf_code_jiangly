//url:https://codeforces.com/contest/1700/problem/A
//time:2022-06-19 12:06:25
//name:A-OptimalPath

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    i64 ans = 1LL * m * (m + 1) / 2 + 1LL * m * n * (n + 1) / 2 - m;
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

