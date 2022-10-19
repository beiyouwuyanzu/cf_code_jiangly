// url:https://codeforces.com/contest/734/problem/E
// time:2021-12-23 19:08:49
// name:E-AntonandTree

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> color(n);
    
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        std::cin >> color[i];
    }
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    std::vector<int> dis;
    auto bfs = [&](int s) {
        dis.assign(n, -1);
        dis[s] = 0;
        std::queue<int> q;
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (auto v : adj[u]) {
                if (dis[v] == -1) {
                    dis[v] = dis[u] + (color[u] ^ color[v]);
                    q.push(v);
                }
            }
        }
        
        return std::max_element(dis.begin(), dis.end()) - dis.begin();
    };
    
    int u = bfs(0);
    int v = bfs(u);
    
    std::cout << (dis[v] + 1) / 2 << "\n";
    
    return 0;
}
