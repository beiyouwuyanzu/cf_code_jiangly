//url:https://codeforces.com/contest/1606/problem/A
//time:2022-06-09 16:56:34
//name:A-ABBalance

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s;
    std::cin >> s;
    if (s[0] != s.back()) {
        s[0] = s.back();
    }
    std::cout << s << "\n";
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
