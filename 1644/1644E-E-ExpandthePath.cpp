// url:https://codeforces.com/contest/1644/problem/E
// time:2022-02-23 08:22:10
// name:E-ExpandthePath

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    i64 ans = 0;
    
    std::string s;
    std::cin >> s;
    
    auto x = s.find(s[0] ^ 'D' ^ 'R');
    
    if (x == std::string::npos) {
        std::cout << n << "\n";
        return;
    }
    
    int R = n, C = n;
    if (s[0] == 'D') {
        R -= x;
    } else {
        C -= x;
    }
    
    ans = x + 1LL * R * C;
    
    int cx = 0, cy = 0;
    for (int i = x; i < int(s.length()); i++) {
        if (s[i] == 'D') {
            cx++;
            ans -= cy;
        } else {
            cy++;
            ans -= cx;
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
