//url:https://codeforces.com/contest/1615/problem/D
//time:2021-12-24 17:59:52
//name:D-X(or)-masTree

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::vector<std::pair<int, int>>> adj(n);
    std::vector<std::vector<std::pair<int, int>>> e(n);
    
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--;
        v--;
        if (w != -1) {
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--;
        v--;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    
    std::vector<int> c(n, -1);
    
    for (int s = 0; s < n; s++) {
        if (c[s] != -1) {
            continue;
        }
        
        std::queue<int> q;
        q.push(s);
        c[s] = 0;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (auto [v, w] : adj[u]) {
                w = __builtin_parity(w);
                if (c[v] == -1) {
                    c[v] = c[u] ^ w;
                    q.push(v);
                } else if (c[v] != (c[u] ^ w)) {
                    std::cout << "NO\n";
                    return;
                }
            }
        }
    }
    
    std::cout << "YES\n";
    
    std::function<void(int, int)> dfs = [&](int u, int p) {
        for (auto [v, w] : e[u]) {
            if (v == p) {
                continue;
            }
            
            std::cout << u + 1 << " " << v + 1 << " ";
            if (w != -1) {
                std::cout << w << "\n";
            } else {
                std::cout << (c[u] ^ c[v]) << "\n";
            }
            
            dfs(v, u);
        }
    };
    dfs(0, -1);
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

