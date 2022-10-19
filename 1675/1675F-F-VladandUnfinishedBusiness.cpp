// url:https://codeforces.com/contest/1675/problem/F
// time:2022-05-05 17:55:41
// name:F-VladandUnfinishedBusiness

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    int x, y;
    std::cin >> x >> y;
    x--;
    y--;
    
    std::vector<int> a(k);
    for (int i = 0; i < k; i++) {
        std::cin >> a[i];
        a[i]--;
    }
    a.push_back(y);
    
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    std::vector<int> p(n, -1), dep(n);
    auto dfs = [&](auto dfs, int u) -> void {
        for (auto v : adj[u]) {
            if (v == p[u]) {
                continue;
            }
            p[v] = u;
            dep[v] = dep[u] + 1;
            dfs(dfs, v);
        }
    };
    dfs(dfs, x);
    
    int ans = 0;
    std::vector<bool> vis(n);
    vis[x] = true;
    for (auto u : a) {
        while (!vis[u]) {
            vis[u] = true;
            ans += 2;
            u = p[u];
        }
    }
    ans -= dep[y];
    
    std::cout << ans << "\n";
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
