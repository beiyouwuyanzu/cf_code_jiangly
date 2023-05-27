// url:https://codeforces.com/contest/1820/problem/A
// time:2023-04-19 09:55:45
// name:A-Yura'sNewName

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s;
    std::cin >> s;
    
    if (s == "^") {
        std::cout << 1 << "\n";
        return;
    }
    
    s = "^_" + s + "_^";
    int n = s.size();
    
    std::vector<int> p;
    for (int i = 0; i < n; i++) {
        if (s[i] == '^') {
            p.push_back(i);
        }
    }
    int ans = 0;
    for (int i = 1; i < p.size(); i++) {
        ans += std::max(0, p[i] - p[i - 1] - 2);
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
