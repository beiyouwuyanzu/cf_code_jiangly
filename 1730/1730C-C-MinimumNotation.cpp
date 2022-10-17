//url:https://codeforces.com/contest/1730/problem/C
//time:2022-09-25 18:08:55
//name:C-MinimumNotation

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s;
    std::cin >> s;
    
    const int n = s.length();
    
    char x = '9';
    std::array<int, 10> cnt{};
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] <= x) {
            cnt[s[i] - '0']++;
            x = s[i];
        } else {
            cnt[std::min(9, s[i] - '0' + 1)]++;
        }
    }
    
    for (int i = 0; i < 10; i++) {
        std::cout << std::string(cnt[i], '0' + i);
    }
    std::cout << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::cout << std::fixed;
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
