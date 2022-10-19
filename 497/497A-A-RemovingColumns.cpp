// url:https://codeforces.com/contest/497/problem/A
// time:2021-06-20 20:39:59
// name:A-RemovingColumns

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }
    int ans = 0;
    std::vector<bool> less(n - 1);
    for (int j = 0; j < m; j++) {
        bool must = false;
        for (int i = 0; i < n - 1; i++) {
            if (s[i][j] > s[i + 1][j] && !less[i]) {
                must = true;
            }
        }
        if (must) {
            ans++;
        } else {
            for (int i = 0; i < n - 1; i++) {
                if (s[i][j] < s[i + 1][j]) {
                    less[i] = true;
                }
            }
        }
    }
    std::cout << ans << "\n";
    return 0;
}
