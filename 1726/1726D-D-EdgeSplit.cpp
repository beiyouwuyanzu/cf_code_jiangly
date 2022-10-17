//url:https://codeforces.com/contest/1726/problem/D
//time:2022-09-06 17:55:54
//name:D-EdgeSplit

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::vector<std::array<int, 2>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }
    
    std::vector<int> pe(n, -1), parent(n, -1), dep(n);
    std::vector<bool> vis(n);
    
    std::vector<std::array<int, 3>> extra;
    std::set<int> s;
    
    std::string ans(m, '0');
    
    std::function<void(int)> dfs = [&](int u) {
        vis[u] = true;
        for (auto [v, i] : adj[u]) {
            if (!vis[v]) {
                pe[v] = i;
                parent[v] = u;
                dep[v] = dep[u] + 1;
                dfs(v);
                ans[i] = '1';
            } else if (dep[v] > dep[u]) {
                extra.push_back({u, v, i});
                s.insert(u);
                s.insert(v);
            }
        }
    };
    dfs(0);
    
    if (extra.size() == 3 && s.size() == 3) {
        std::vector a(s.begin(), s.end());
        std::sort(a.begin(), a.end(), [&](int i, int j) {
            return dep[i] < dep[j];
        });
        
        for (auto [u, v, i] : extra) {
            if (u == a[0] && v == a[2]) {
                ans[i] = '1';
            }
        }
        ans[pe[a[2]]] = '0';
    }
    
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
