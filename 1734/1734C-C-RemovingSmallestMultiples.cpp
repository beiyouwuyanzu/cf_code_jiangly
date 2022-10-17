//url:https://codeforces.com/contest/1734/problem/C
//time:2022-09-23 15:34:01
//name:C-RemovingSmallestMultiples

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::string t;
    std::cin >> t;
    
    i64 ans = 0;
    
    std::vector<bool> vis(n);
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n && t[j - 1] == '0'; j += i) {
            if (!vis[j - 1]) {
                vis[j - 1] = true;
                ans += i;
            }
        }
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
