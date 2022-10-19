// url:https://codeforces.com/contest/1638/problem/A
// time:2022-02-14 17:47:32
// name:A-Reverse

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
    }
    
    int x = 0;
    while (x < n && p[x] == x + 1) {
        x++;
    }
    
    if (x < n) {
        int y = x;
        while (p[y] != x + 1) {
            y++;
        }
        std::reverse(p.begin() + x, p.begin() + y + 1);
    }
    
    
    for (int i = 0; i < n; i++) {
        std::cout << p[i] << " \n"[i == n - 1];
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
