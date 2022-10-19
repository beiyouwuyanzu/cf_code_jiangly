// url:https://codeforces.com/contest/1616/problem/F
// time:2021-12-29 19:37:04
// name:F-TricolorTriangles

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector adj(n, std::vector(n, -1));
    std::vector<std::vector<int>> f;
    std::vector<int> g;
    std::vector<int> color(m);
    
    for (int i = 0; i < m; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        a--;
        b--;
        if (c > 0) {
            c--;
        }
        adj[a][b] = adj[b][a] = i;
        if (c != -1) {
            f.emplace_back(m);
            f.back()[i] = 1;
            g.push_back(c);
        }
    }
    
    for (int a = 0; a < n; a++) {
        for (int b = a + 1; b < n; b++) {
            if (adj[a][b] == -1) {
                continue;
            }
            for (int c = b + 1; c < n; c++) {
                if (adj[a][c] == -1 || adj[b][c] == -1) {
                    continue;
                }
                f.emplace_back(m);
                f.back()[adj[a][b]] = f.back()[adj[b][c]] = f.back()[adj[a][c]] = 1;
                g.push_back(0);
            }
        }
    }
    
    const int r = f.size();
    int rank = 0;
    for (int i = 0; i < m; i++) {
        int j = rank;
        while (j < r && f[j][i] == 0) {
            j++;
        }
        if (j == r) {
            continue;
        }
        std::swap(f[j], f[rank]);
        std::swap(g[j], g[rank]);
        j = rank;
        rank++;
        
        if (f[j][i] == 2) {
            for (int y = i; y < m; y++) {
                f[j][y] = (3 - f[j][y]) % 3;
            }
            g[j] = (3 - g[j]) % 3;
        }
        
        for (int x = 0; x < r; x++) {
            if (f[x][i] != 0 && x != j) {
                int v = f[x][i];
                for (int y = i; y < m; y++) {
                    f[x][y] = (f[x][y] - v * f[j][y] % 3 + 3) % 3;
                }
                g[x] = (g[x] - v * g[j] % 3 + 3) % 3;
            }
        }
    }
    for (int i = rank; i < r; i++) {
        if (g[i] != 0) {
            std::cout << "-1\n";
            return;
        }
    }
    
    for (int i = rank - 1; i >= 0; i--) {
        int j = 0;
        while (f[i][j] == 0) {
            j++;
        }
        color[j] = g[i];
    }
    
    for (int i = 0; i < m; i++) {
        std::cout << color[i] + 1 << " \n"[i == m - 1];
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

