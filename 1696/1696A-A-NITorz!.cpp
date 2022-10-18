//url:https://codeforces.com/contest/1696/problem/A
//time:2022-06-25 17:52:27
//name:A-NITorz!

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, z;
    std::cin >> n >> z;
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int a;
        std::cin >> a;
        ans = std::max(ans, a | z);
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

