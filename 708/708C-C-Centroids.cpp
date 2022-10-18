//url:https://codeforces.com/contest/708/problem/C
//time:2021-12-24 06:02:32
//name:C-Centroids

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    std::vector<int> siz(n), f(n), g(n), up(n);
    
    std::function<void(int, int)> dfs1 = [&](int u, int p) {
        siz[u] = 1;
        for (auto v : adj[u]) {
            if (v == p) {
                continue;
            }
            dfs1(v, u);
            siz[u] += siz[v];
            f[u] = std::max(f[u], siz[v]);
            g[u] = std::max(g[u], g[v]);
        }
        if (siz[u] * 2 <= n) {
            g[u] = siz[u];
        }
    };
    dfs1(0, -1);
    
    std::function<void(int, int)> dfs2 = [&](int u, int p) {
        f[u] = std::max(f[u], n - siz[u]);
        int mx[2] = {up[u], 0};
        for (auto v : adj[u]) {
            if (v == p) {
                continue;
            }
            
            int x = g[v];
            if (x > mx[0]) {
                mx[1] = mx[0];
                mx[0] = x;
            } else if (x > mx[1]) {
                mx[1] = x;
            }
        }
        for (auto v : adj[u]) {
            if (v == p) {
                continue;
            }
            int x = g[v];
            up[v] = x == mx[0] ? mx[1] : mx[0];
            if (2 * (n - siz[v]) <= n) {
                up[v] = n - siz[v];
            }
            dfs2(v, u);
        }
        int x = 0;
        if (f[u] == n - siz[u]) {
            x = up[u];
        }
        for (auto v : adj[u]) {
            if (v == p) {
                continue;
            }
            if (f[u] == siz[v]) {
                x = g[v];
            }
        }
        f[u] -= x;
    };
    dfs2(0, -1);
    
    for (int i = 0; i < n; i++) {
        std::cout << (2 * f[i] <= n) << " \n"[i == n - 1];
    }
    
    return 0;
}
