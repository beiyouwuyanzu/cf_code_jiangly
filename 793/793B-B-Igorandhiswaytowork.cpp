//url:https://codeforces.com/contest/793/problem/B
//time:2021-01-03 17:33:35
//name:B-Igorandhiswaytowork

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    int xs = -1, ys = -1;
    int xt = -1, yt = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'S') {
                xs = i;
                ys = j;
            }
            if (a[i][j] == 'T') {
                xt = i;
                yt = j;
            }
        }
    }
    std::vector<std::vector<bool>> vis(n, std::vector<bool>(m));
    vis[xs][ys] = true;
    for (int t = 0; t < 3; t++) {
        std::vector<std::vector<bool>> L(vis), R(vis), U(vis), D(vis);
        for (int i = 0; i < n; i++) {
            for (int j = m - 2; j >= 0; j--) {
                L[i][j] = (L[i][j] || L[i][j + 1]) && a[i][j] != '*';
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < m; j++) {
                R[i][j] = (R[i][j] || R[i][j - 1]) && a[i][j] != '*';
            }
        }
        for (int i = n - 2; i >= 0; i--) {
            for (int j = 0; j < m; j++) {
                U[i][j] = (U[i][j] || U[i + 1][j]) && a[i][j] != '*';
            }
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                D[i][j] = (D[i][j] || D[i - 1][j]) && a[i][j] != '*';
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                vis[i][j] = L[i][j] || R[i][j] || U[i][j] || D[i][j];
            }
        }
    }
    if (vis[xt][yt]) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}
