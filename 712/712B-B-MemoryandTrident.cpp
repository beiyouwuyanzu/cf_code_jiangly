// url:https://codeforces.com/contest/712/problem/B
// time:2023-03-15 11:21:43
// name:B-MemoryandTrident

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s;
    std::cin >> s;
    
    if (s.size() % 2 == 1) {
        std::cout << -1 << "\n";
        return 0;
    }
    
    int x = 0, y = 0;
    for (auto c : s) {
        if (c == 'L') {
            x--;
        } else if (c == 'R') {
            x++;
        } else if (c == 'U') {
            y++;
        } else {
            y--;
        }
    }
    
    int ans = (std::abs(x) + std::abs(y)) / 2;
    std::cout << ans << "\n";
    
    return 0;
}

