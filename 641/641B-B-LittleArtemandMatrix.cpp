// url:https://codeforces.com/contest/641/problem/B
// time:2021-07-09 21:19:23
// name:B-LittleArtemandMatrix

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, q;
    std::cin >> n >> m >> q;
    
    std::vector a(n, std::vector<int>(m));
    
    std::vector idx(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            idx[i][j] = i * m + j;
        }
    }

    for (int i = 0; i < q; i++) {
        int t;
        std::cin >> t;
        
        if (t == 1) {
            int r;
            std::cin >> r;
            r--;
            std::rotate(idx[r].begin(), idx[r].begin() + 1, idx[r].end());
        } else if (t == 2) {
            int c;
            std::cin >> c;
            c--;
            int first = idx[0][c];
            for (int j = 0; j < n - 1; j++) {
                idx[j][c] = idx[j + 1][c];
            }
            idx[n - 1][c] = first;
        } else {
            int r, c, x;
            std::cin >> r >> c >> x;
            r--;
            c--;
            int u = idx[r][c];
            a[u / m][u % m] = x;
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << a[i][j] << " \n"[j == m - 1];
        }
    }
    
    return 0;
}
