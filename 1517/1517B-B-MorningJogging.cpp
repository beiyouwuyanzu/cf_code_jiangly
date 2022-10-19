// url:https://codeforces.com/contest/1517/problem/B
// time:2021-04-23 17:45:04
// name:B-MorningJogging

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
        std::vector<std::vector<int>> b(n, std::vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                std::cin >> b[i][j];
            }
        }
        std::vector<int> p(n * m);
        std::iota(p.begin(), p.end(), 0);
        std::sort(p.begin(), p.end(), [&](int i, int j) {
            return b[i / m][i % m] < b[j / m][j % m];
        });
        std::vector<std::vector<int>> a(n, std::vector<int>(m));
        for (int i = 0; i < m; i++) {
            a[p[i] / m][i] = b[p[i] / m][p[i] % m];
        }
        std::vector<int> cur(n);
        for (int i = m; i < n * m; i++) {
            int r = p[i] / m;
            while (a[r][cur[r]]) {
                cur[r]++;
            }
            a[r][cur[r]] = b[r][p[i] % m];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                std::cout << a[i][j] << " \n"[j == m - 1];
            }
        }
    }
    return 0;
}
