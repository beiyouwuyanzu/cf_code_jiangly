//url:https://codeforces.com/contest/1694/problem/B
//time:2022-06-27 11:21:45
//name:B-ParanoidString

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 && s[i] != s[i - 1]) {
            ans += i + 1;
        } else {
            ans += 1;
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

