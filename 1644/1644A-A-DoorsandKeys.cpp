// url:https://codeforces.com/contest/1644/problem/A
// time:2022-02-23 09:48:27
// name:A-DoorsandKeys

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s;
    std::cin >> s;
    
    std::set<char> keys;
    for (auto c : s) {
        if (std::islower(c)) {
            keys.insert(c);
        } else if (!keys.count(std::tolower(c))) {
            std::cout << "NO\n";
            return;
        }
    }
    
    std::cout << "YES\n";
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
