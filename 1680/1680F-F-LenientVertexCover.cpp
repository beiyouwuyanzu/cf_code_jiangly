// url:https://codeforces.com/contest/1680/problem/F
// time:2022-05-16 20:45:33
// name:F-LenientVertexCover

#include <bits/stdc++.h>

using i64 = long long;
using u64 = uint64_t;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    std::vector<int> color(n, -1), p(n), dep(n);
    p[0] = -1;
    color[0] = 0;
    std::function<void(int)> dfs = [&](int u) {
        for (auto v : adj[u]) {
            if (color[v] == -1) {
                p[v] = u;
                dep[v] = dep[u] + 1;
                color[v] = color[u] ^ 1;
                dfs(v);
            }
        }
    };
    dfs(0);
    
    std::vector<int> f(n);
    
    int badEdges = 0;
    bool bad = false;
    for (int u = 0; u < n; u++) {
        for (auto v : adj[u]) {
            if (color[u] == 0 && color[v] == 0) {
                bad = true;
            }
            if (dep[u] < dep[v] && p[v] != u) {
                if (color[u] == color[v]) {
                    badEdges++;
                    f[v]++;
                    f[u]--;
                } else {
                    f[v]--;
                    f[u]++;
                }
            }
        }
    }
    
    if (badEdges <= 1) {
        if (bad) {
            for (int i = 0; i < n; i++) {
                color[i] ^= 1;
            }
        }
        std::cout << "YES\n";
        for (int i = 0; i < n; i++) {
            std::cout << color[i];
        }
        std::cout << "\n";
        return;
    }
    
    dfs = [&](int u) {
        for (auto v : adj[u]) {
            if (p[v] == u) {
                dfs(v);
                f[u] += f[v];
            }
        }
    };
    dfs(0);
    
    for (int i = 1; i < n; i++) {
        if (f[i] == badEdges) {
            dfs = [&](int u) {
                color[u] ^= 1;
                for (auto v : adj[u]) {
                    if (p[v] == u) {
                        dfs(v);
                    }
                }
            };
            dfs(i);
            if (color[i] == 0) {
                for (int i = 0; i < n; i++) {
                    color[i] ^= 1;
                }
            }
            std::cout << "YES\n";
            for (int i = 0; i < n; i++) {
                std::cout << color[i];
            }
            std::cout << "\n";
            return;
        }
    }
    
    std::cout << "NO\n";
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
