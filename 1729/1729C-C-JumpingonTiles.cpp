//url:https://codeforces.com/contest/1729/problem/C
//time:2022-09-12 17:43:13
//name:C-JumpingonTiles

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s;
    std::cin >> s;
    
    int n = s.length();
    std::vector<int> p[26];
    
    for (int i = 0; i < n; i++) {
        p[s[i] - 'a'].push_back(i);
    }
    
    int x = s[0] - 'a', y = s[n - 1] - 'a';
    if (x > y) {
        std::swap(x, y);
        for (int i = 0; i < 26; i++) {
            std::reverse(p[i].begin(), p[i].end());
        }
    }
    std::vector<int> ans;
    for (int i = x; i <= y; i++) {
        ans.insert(ans.end(), p[i].begin(), p[i].end());
    }
    std::cout << std::abs(s[0] - s[n - 1]) << " " << ans.size() << "\n";
    if (ans[0]) {
        std::reverse(ans.begin(), ans.end());
    }
    for (int i = 0; i < int(ans.size()); i++) {
        std::cout << ans[i] + 1 << " \n"[i == int(ans.size()) - 1];
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
