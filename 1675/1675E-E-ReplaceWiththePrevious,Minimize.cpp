// url:https://codeforces.com/contest/1675/problem/E
// time:2022-05-05 17:51:35
// name:E-ReplaceWiththePrevious,Minimize

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    std::string s;
    std::cin >> s;
    
    int mx = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] - 'a' > k) {
            char l = s[i] - (k - mx);
            char r = s[i];
            for (int j = 0; j < n; j++) {
                if (l <= s[j] && s[j] <= r) {
                    s[j] = l;
                }
            }
            break;
        }
        mx = std::max(mx, s[i] - 'a');
    }
    
    for (int i = 0; i < n; i++) {
        if (s[i] <= 'a' + mx) {
            s[i] = 'a';
        }
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
