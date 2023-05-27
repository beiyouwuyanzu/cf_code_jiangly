// url:https://codeforces.com/contest/1809/problem/A
// time:2023-03-23 17:42:45
// name:A-Garland

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s;
    std::cin >> s;
    
    std::sort(s.begin(), s.end());
    
    if (s[0] == s[3]) {
        std::cout << -1 << "\n";
    } else if (s[0] == s[2] || s[1] == s[3]) {
        std::cout << 6 << "\n";
    } else {
        std::cout << 4 << "\n";
    }
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
