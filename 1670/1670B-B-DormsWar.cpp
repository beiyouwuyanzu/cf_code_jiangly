// url:https://codeforces.com/contest/1670/problem/B
// time:2022-05-06 18:38:52
// name:B-DormsWar

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    bool special[26] = {};
    int k;
    std::cin >> k;
    for (int i = 0; i < k; i++) {
        char c;
        std::cin >> c;
        special[c - 'a'] = true;
    }
    
    int ans = 0;
    int cnt = 0;
    for (auto c : s.substr(1)) {
        if (!special[c - 'a']) {
            cnt++;
        } else {
            ans = std::max(ans, cnt + 1);
            cnt = 0;
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
