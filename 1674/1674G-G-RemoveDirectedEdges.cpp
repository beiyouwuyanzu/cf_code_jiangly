// url:https://codeforces.com/contest/1674/problem/G
// time:2022-05-02 18:07:45
// name:G-RemoveDirectedEdges

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::vector<int>> adj(n);
    std::vector<int> in(n), out(n), cur(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        in[v]++;
        out[u]++;
        cur[v]++;
    }
    
    std::queue<int> q;
    for (int i = 0; i < n; i++) {
        if (!cur[i]) {
            q.push(i);
        }
    }
    
    int ans = 1;
    std::vector<int> f(n, 1);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        ans = std::max(ans, f[u]);
        
        for (auto v : adj[u]) {
            if (out[u] > 1 && in[v] > 1) {
                f[v] = std::max(f[v], f[u] + 1);
            }
            if (!--cur[v]) {
                q.push(v);
            }
        }
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
