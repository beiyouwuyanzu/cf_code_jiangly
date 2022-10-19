// url:https://codeforces.com/contest/1744/problem/A
// time:2022-10-18 14:05:09
// name:A-NumberReplacement

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::string s;
    std::cin >> s;
    
    std::map<int, char> mp;
    for (int i = 0; i < n; i++) {
        if (!mp.contains(a[i])) {
            mp[a[i]] = s[i];
        } else if (mp[a[i]] != s[i]) {
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
