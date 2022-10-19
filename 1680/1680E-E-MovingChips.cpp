// url:https://codeforces.com/contest/1680/problem/E
// time:2022-05-16 19:54:32
// name:E-MovingChips

#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1E9;

void solve() {
    int n;
    std::cin >> n;
    
    std::array<std::string, 2> s;
    std::cin >> s[0] >> s[1];
    
    int l = 0, r = n - 1;
    while (s[0][l] == '.' && s[1][l] == '.') {
        l++;
    }
    while (s[0][r] == '.' && s[1][r] == '.') {
        r--;
    }
    
    std::array<int, 2> f {-1, -1};
    
    for (int i = l; i <= r; i++) {
        std::array<int, 2> g;
        g[0] = g[1] = std::min(f[0], f[1]) + 2;
        for (int j = 0; j < 2; j++) {
            if (s[!j][i] == '.') {
                g[j] = std::min(g[j], f[j]) + 1;
            }
        }
        f = g;
    }
    
    std::cout << std::min(f[0], f[1]) << "\n";
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
