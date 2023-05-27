// url:https://codeforces.com/contest/1821/problem/A
// time:2023-04-20 19:02:17
// name:A-Matching

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s;
    std::cin >> s;
    
    int ans = 1;
    for (int i = 0; i < s.size(); i++) {
        ans *= (s[i] == '?' ? 10 : 1) - ((s[i] == '?' || s[i] == '0') && !i);
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
