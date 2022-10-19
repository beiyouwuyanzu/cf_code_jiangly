// url:https://codeforces.com/contest/1511/problem/A
// time:2022-06-27 16:27:24
// name:A-ReviewSite

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        
        ans += (x != 2);
    }
    
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
