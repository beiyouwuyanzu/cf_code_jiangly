// url:https://codeforces.com/contest/1495/problem/C
// time:2021-03-11 11:40:46
// name:C-GardenoftheSun

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n, m;
        std::cin >> n >> m;
        std::vector<std::string> s(n);
        for (int i = 0; i < n; i++) {
            std::cin >> s[i];
        }
        for (int i = 0; i < n; i += 3) {
            s[i] = std::string(m, 'X');
            if (i + 3 >= n) {
                if (i + 2 < n) {
                    for (int j = 0; j < m; j++) {
                        if (s[i + 1][j] == 'X' || s[i + 2][j] == 'X') {
                            s[i + 1][j] = s[i + 2][j] = 'X';
                        }
                    }
                }
                continue;
            }
            bool ok = false;
            for (int j = 0; j < m; j++) {
                if (s[i + 1][j] == 'X' || s[i + 2][j] == 'X') {
                    s[i + 1][j] = s[i + 2][j] = 'X';
                    ok = true;
                    break;
                }
            }
            if (!ok) {
                s[i + 1][0] = s[i + 2][0] = 'X';
            }
        }
        for (int i = 0; i < n; i++) {
            std::cout << s[i] << "\n";
        }
    }
    return 0;
}

