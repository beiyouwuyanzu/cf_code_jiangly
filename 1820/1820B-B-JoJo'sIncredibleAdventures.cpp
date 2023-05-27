// url:https://codeforces.com/contest/1820/problem/B
// time:2023-04-19 09:52:07
// name:B-JoJo'sIncredibleAdventures

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s;
    std::cin >> s;
    
    int n = s.size();
    if (std::count(s.begin(), s.end(), '0') == 0) {
        std::cout << 1LL * n * n << "\n";
        return;
    }
    
    s = s + s;
    i64 ans = 0;
    for (int i = 0, j; i < n; i++) {
        if (s[i] == '1') {
            j = i;
            while (s[j] == '1') {
                j++;
            }
            int d = j - i + 1;
            ans = std::max(ans, 1LL * (d / 2) * (d - d / 2));
            i = j;
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
