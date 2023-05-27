// url:https://codeforces.com/contest/598/problem/A
// time:2023-04-23 17:57:14
// name:A-TrickySum

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    i64 ans = 1LL * n * (n+1) / 2;
    int m = 1 << std::__lg(n);
    ans -= 2 * (2LL * m - 1);
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
