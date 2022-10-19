// url:https://codeforces.com/contest/1742/problem/F
// time:2022-10-13 18:11:56
// name:F-Smaller

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int q;
    std::cin >> q;
    
    i64 lens = 1, lent = 1;
    
    char mins = 'a', maxs = 'a';
    char mint = 'a', maxt = 'a';
    
    for (int i = 0; i < q; i++) {
        int o, k;
        std::string s;
        std::cin >> o >> k >> s;
        
        for (auto c : s) {
            if (o == 1) {
                mins = std::min(mins, c);
                maxs = std::max(maxs, c);
                lens += k;
            } else {
                mint = std::min(mint, c);
                maxt = std::max(maxt, c);
                lent += k;
            }
        }
        
        if (mins < maxt || (mins == maxt && mins == maxs && mint == maxt && lens < lent)) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
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

