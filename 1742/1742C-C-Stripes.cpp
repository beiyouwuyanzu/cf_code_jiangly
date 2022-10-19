// url:https://codeforces.com/contest/1742/problem/C
// time:2022-10-13 18:12:57
// name:C-Stripes

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s[8];
    for (int i = 0; i < 8; i++) {
        std::cin >> s[i];
    }
    
    for (int i = 0; i < 8; i++) {
        if (s[i] == std::string(8, s[i][0]) && s[i][0] == 'R') {
            std::cout << s[i][0] << "\n";
            return;
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < i; j++) {
            std::swap(s[i][j], s[j][i]);
        }
    }
    for (int i = 0; i < 8; i++) {
        if (s[i] == std::string(8, s[i][0]) && s[i][0] == 'B') {
            std::cout << s[i][0] << "\n";
            return;
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

