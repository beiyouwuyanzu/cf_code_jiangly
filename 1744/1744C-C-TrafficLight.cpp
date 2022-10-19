// url:https://codeforces.com/contest/1744/problem/C
// time:2022-10-18 14:10:35
// name:C-TrafficLight

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    char c;
    std::cin >> n >> c;
    
    std::string s;
    std::cin >> s;
    
    int ans = 0, x = 0;
    for (int t = 0; t < 2; t++) {
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == 'g') {
                x = 0;
            } else {
                x++;
            }
            if (s[i] == c && t) {
                ans = std::max(ans, x);
            }
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
