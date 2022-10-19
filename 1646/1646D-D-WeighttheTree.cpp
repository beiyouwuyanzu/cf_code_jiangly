// url:https://codeforces.com/contest/1646/problem/D
// time:2022-03-04 19:57:17
// name:D-WeighttheTree

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    if (n == 2) {
        std::cout << "2 2\n";
        std::cout << "1 1\n";
        return 0;
    }
    
    std::vector<int> deg(n);
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    
    std::vector<std::pair<int, i64>> f(n), g(n);
    auto dfs = [&](auto self, int u, int p) -> void {
        f[u] = {1, -deg[u]};
        for (auto v : adj[u]) {
            if (v == p) {
                continue;
            }
            self(self, v, u);
            f[u].first += g[v].first;
            f[u].second += g[v].second;
            auto mx = std::max(f[v], g[v]);
            g[u].first += mx.first;
            g[u].second += mx.second;
        }
    };
    dfs(dfs, 0, -1);
    
    auto ans = std::max(f[0], g[0]);
    std::cout << ans.first << " " << -ans.second + n - ans.first << "\n";
    
    std::vector<int> w(n);
    
    auto rec = [&](auto self, int u, int p, int t) -> void {
        if (t == 0) {
            w[u] = deg[u];
        } else {
            w[u] = 1;
        }
        for (auto v : adj[u]) {
            if (v == p) {
                continue;
            }
            if (t == 0 || f[v] < g[v]) {
                self(self, v, u, 1);
            } else {
                self(self, v, u, 0);
            }
        }
    };
    rec(rec, 0, -1, (f[0] == ans ? 0 : 1));
    
    for (int i = 0; i < n; i++) {
        std::cout << w[i] << " \n"[i == n - 1];
    }
    
    return 0;
}
