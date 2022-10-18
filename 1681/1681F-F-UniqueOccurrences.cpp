//url:https://codeforces.com/contest/1681/problem/F
//time:2022-05-23 18:39:29
//name:F-UniqueOccurrences

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<std::vector<std::array<int, 2>>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v, x;
        std::cin >> u >> v >> x;
        u--;
        v--;
        x--;
        adj[u].push_back({v, x});
        adj[v].push_back({u, x});
    }
    
    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < n; i++) {
        g[i].push_back(n + i);
    }
    
    std::vector<int> siz(n), f(n + n);
    for (int i = 0; i < n; i++) {
        f[i + n] = n;
    }
    
    i64 ans = 0;
    std::function<void(int, int)> dfs1 = [&](int u, int p) {
        siz[u] = 1;
        for (auto [v, x] : adj[u]) {
            if (v == p) {
                continue;
            }
            g[x].push_back(v);
            dfs1(v, u);
            siz[u] += siz[v];
            g[x].pop_back();
            f[g[x].back()] -= siz[v];
        }
        f[u] += siz[u];
    };
    dfs1(0, -1);
    
    std::function<void(int, int)> dfs2 = [&](int u, int p) {
        for (auto [v, x] : adj[u]) {
            if (v == p) {
                continue;
            }
            ans += 1LL * f[v] * f[g[x].back()];
            g[x].push_back(v);
            dfs2(v, u);
            g[x].pop_back();
        }
    };
    dfs2(0, -1);
    
    std::cout << ans << "\n";
    
    return 0;
}
