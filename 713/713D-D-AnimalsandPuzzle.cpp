// url:https://codeforces.com/contest/713/problem/D
// time:2021-07-07 16:33:11
// name:D-AnimalsandPuzzle

#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1000;

int f[N][N][10][10];

int query(int l, int d, int r, int u) {
    int k1 = std::__lg(r - l);
    int k2 = std::__lg(u - d);
    return std::max({f[l][d][k1][k2], f[r - (1 << k1)][d][k1][k2], f[l][u - (1 << k2)][k1][k2], f[r - (1 << k1)][u - (1 << k2)][k1][k2]});
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector a(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 0) {
                f[i][j][0][0] = 0;
            } else {
                f[i][j][0][0] = 1;
                if (i > 0 && j > 0) {
                    f[i][j][0][0] += std::min({f[i - 1][j][0][0], f[i][j - 1][0][0], f[i - 1][j - 1][0][0]});
                }
            }
        }
    }
    
    for (int k1 = 0; k1 < 10; k1++) {
        for (int k2 = 0; k2 < 10; k2++) {
            for (int i = 0; i + (1 << k1) <= n; i++) {
                for (int j = 0; j + (1 << k2) <= m; j++) {
                    if (k1 == 0 && j + (2 << k2) <= m) {
                        f[i][j][k1][k2 + 1] = std::max(f[i][j][k1][k2], f[i][j + (1 << k2)][k1][k2]);
                    }
                    if (i + (2 << k1) <= n) {
                        f[i][j][k1 + 1][k2] = std::max(f[i][j][k1][k2], f[i + (1 << k1)][j][k1][k2]);
                    }
                }
            }
        }
    }
    
    int t;
    std::cin >> t;
    while (t--) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        x1--;
        y1--;
        int lo = 0, hi = std::min(x2 - x1, y2 - y1);
        while (lo < hi) {
            int a = (lo + hi + 1) / 2;
            if (query(x1 + a - 1, y1 + a - 1, x2, y2) >= a) {
                lo = a;
            } else {
                hi = a - 1;
            }
        }
        std::cout << lo << "\n";
    }
    
    return 0;
}
