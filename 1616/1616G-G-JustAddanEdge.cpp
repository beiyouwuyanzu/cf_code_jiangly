// url:https://codeforces.com/contest/1616/problem/G
// time:2021-12-29 21:07:24
// name:G-JustAddanEdge

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    n += 2;
    
    std::vector<std::pair<int, int>> edges;
    std::vector<bool> adj(n);
    
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        if (u + 1 == v) {
            cnt++;
            adj[u] = true;
        }
        edges.emplace_back(u, v);
    }
    adj[0] = adj[n - 2] = true;
    cnt += 2;
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            edges.emplace_back(0, i);
        }
        if (i != n - 1 && i != 0) {
            edges.emplace_back(i, n - 1);
        }
    }
    
    if (cnt == n - 1) {
        std::cout << 1LL * (n - 2) * (n - 3) / 2 << "\n";
        return;
    }
    
    std::vector<int> l(n), r(n);
    for (int i = 0, j = 0; i < n; i = j + 1) {
        j = i;
        while (adj[j]) {
            j++;
        }
        for (int x = i; x <= j; x++) {
            l[x] = i;
            r[x] = j;
        }
    }
    
    std::vector<std::vector<int>> e1(n), e2(n);
    for (auto [u, v] : edges) {
        if (u + 1 == v) {
            continue;
        }
        if (l[u] == l[v] || (r[u] == l[v] - 1 && (r[u] == u || l[v] == v)) || (u == r[u] && v == l[v] && r[u + 1] == v - 1)) {
            e1[u].push_back(v - 1);
            e2[v - 1].push_back(u);
        }
    }
    
    int x = r[0];
    int y = l[n - 1];
    
    auto bfs = [&](auto e, int x, int t) {
        std::vector<int> xs;
        std::queue<int> q;
        q.push(2 * x + 1);
        
        std::vector<bool> vis(n * 2);
        vis[2 * x + 1] = true;
        
        int c01 = 0, c0 = 0, c1 = 0;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            int t = u % 2;
            
            for (auto v : e[u / 2]) {
                if (!vis[v * 2 + !t]) {
                    vis[v * 2 + !t] = true;
                    q.push(v * 2 + !t);
                }
            }
        }
        
        if (t == 0) {
            for (int i = 0; i <= x; i++) {
                if (vis[2 * i] && vis[2 * i + 1]) {
                    c01++;
                } else if (vis[2 * i]) {
                    c0++;
                } else if (vis[2 * i + 1]) {
                    c1++;
                }
            }
        } else {
            for (int i = y - 1; i < n - 1; i++) {
                if (vis[2 * i] && vis[2 * i + 1]) {
                    c01++;
                } else if (vis[2 * i]) {
                    c0++;
                } else if (vis[2 * i + 1]) {
                    c1++;
                }
            }
        }
        
        return std::tuple(c01 + c0 + c1, c0, c1);
    };
    
    auto [u, u0, u1] = bfs(e2, x, 0);
    auto [v, v0, v1] = bfs(e1, x, 1);
    
    i64 ans = 1LL * u * v - 1LL * u0 * v1 - 1LL * u1 * v0;
    
    if (x + 1 == y) {
        ans--;
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

