// url:https://codeforces.com/contest/1635/problem/E
// time:2022-02-20 18:28:51
// name:E-Cars

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> type(m), u(m), v(m);
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        std::cin >> type[i] >> u[i] >> v[i];
        u[i]--;
        v[i]--;
        adj[u[i]].push_back(v[i]);
        adj[v[i]].push_back(u[i]);
    }
    
    std::vector<int> ori(n, -1);
    
    auto dfs = [&](auto self, int u) -> void {
        for (auto v : adj[u]) {
            if (ori[v] == -1) {
                ori[v] = ori[u] ^ 1;
                self(self, v);
            } else if (ori[u] == ori[v]) {
                std::cout << "NO\n";
                std::exit(0);
            }
        }
    };
    for (int i = 0; i < n; i++) {
        if (ori[i] == -1) {
            ori[i] = 0;
            dfs(dfs, i);
        }
    }
    
    for (int i = 0; i < n; i++) {
        adj[i].clear();
    }
    
    std::queue<int> q;
    std::vector<int> deg(n);
    for (int i = 0; i < m; i++) {
        if (type[i] - 1 == ori[u[i]]) {
            adj[u[i]].push_back(v[i]);
            deg[v[i]]++;
        } else {
            adj[v[i]].push_back(u[i]);
            deg[u[i]]++;
        }
    }
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }
    
    std::vector<int> coor(n);
    int cur = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        coor[u] = cur++;
        
        for (auto v : adj[u]) {
            if (--deg[v] == 0) {
                q.push(v);
            }
        }
    }
    
    if (cur != n) {
        std::cout << "NO\n";
        return 0;
    }
    
    std::cout << "YES\n";
    
    for (int i = 0; i < n; i++) {
        std::cout << "LR"[ori[i]] << " " << coor[i] << "\n";
    }
    
    return 0;
}
