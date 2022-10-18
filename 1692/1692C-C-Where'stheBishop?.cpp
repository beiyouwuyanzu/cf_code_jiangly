//url:https://codeforces.com/contest/1692/problem/C
//time:2022-06-14 17:40:13
//name:C-Where'stheBishop?

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s[8];
    for (int i = 0; i < 8; i++) {
        std::cin >> s[i];
    }
    for (int x = 1; x < 7; x++) {
        for (int y = 1; y < 7; y++) {
            bool ok = true;
            
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (s[x - 1 + i][y - 1 + j] != "#."[(i == 1) ^ (j == 1)]) {
                        ok = false;
                    }
                }
            }
            
            if (ok) {
                std::cout << x + 1 << " " << y + 1 << "\n";
                return;
            }
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

