//url:https://codeforces.com/contest/1696/problem/F
//time:2022-06-25 18:24:26
//name:F-TreeRecovery

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector f(n, std::vector<std::string>(n));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            std::cin >> f[i][j];
            f[j][i] = f[i][j];
        }
    }
    
    for (int x = 1; x < n; x++) {
        std::vector<bool> vis(n);
        vis[0] = true;
        vis[x] = true;
        std::vector<std::array<int, 2>> edges;
        edges.push_back({0, x});
        
        std::function<void(int, int)> check = [&](int u, int v) {
            for (int i = 0; i < n; i++) {
                if (vis[i] || f[i][u][v] == '0') {
                    continue;
                }
                vis[i] = true;
                edges.push_back({v, i});
                check(v, i);
            }
        };
        
        check(0, x);
        check(x, 0);
        
        if (int(edges.size()) != n - 1) {
            continue;
        }
        
        bool ok = true;
        
        std::vector<std::vector<int>> adj(n);
        for (auto [u, v] : edges) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        std::vector dis(n, std::vector<int>(n));
        for (int i = 0; i < n; i++) {
            std::function<void(int, int)> dfs = [&](int u, int p) {
                for (auto v : adj[u]) {
                    if (v == p) {
                        continue;
                    }
                    dis[i][v] = dis[i][u] + 1;
                    dfs(v, u);
                }
            };
            dfs(i, -1);
        }
        
        for (int x = 0; x < n; x++) {
            for (int y = x + 1; y < n; y++) {
                for (int z = 0; z < n; z++) {
                    if ((f[x][y][z] == '1') != (dis[x][z] == dis[y][z])) {
                        ok = false;
                    }
                }
            }
        }
        if (ok) {
            std::cout << "Yes\n";
            for (auto [u, v] : edges) {
                std::cout << u + 1 << " " << v + 1 << "\n";
            }
            return;
        }
    }
    
    std::cout << "No\n";
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

