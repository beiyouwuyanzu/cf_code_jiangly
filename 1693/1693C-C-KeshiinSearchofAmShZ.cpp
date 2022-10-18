//url:https://codeforces.com/contest/1693/problem/C
//time:2022-06-16 17:54:42
//name:C-KeshiinSearchofAmShZ

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> deg(n);
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[v].push_back(u);
        deg[u]++;
    }
    
    std::priority_queue<std::array<int, 2>, std::vector<std::array<int, 2>>, std::greater<>> h;
    
    h.push({ 0, n - 1 });
    std::vector<int> dis(n, -1);
    
    while (!h.empty()) {
        auto [d, v] = h.top();
        h.pop();
        
        if (dis[v] != -1) {
            continue;
        }
        dis[v] = d;
        
        for (auto u : adj[v]) {
            deg[u]--;
            h.push({ d + deg[u] + 1, u });
        }
    }
    
    std::cout << dis[0] << "\n";
    
    return 0;
}

