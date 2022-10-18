//url:https://codeforces.com/contest/765/problem/E
//time:2021-07-12 15:13:33
//name:E-TreeFolding

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<std::vector<int>> e(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    
    std::vector<int> parent(n), dis(n);
    auto bfs = [&](int s) {
        parent.assign(n, -1);
        dis.assign(n, -1);
        
        std::queue<int> que;
        que.push(s);
        dis[s] = 0;
        
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            
            for (auto v : e[u]) {
                if (dis[v] >= 0) {
                    continue;
                }
                
                parent[v] = u;
                dis[v] = dis[u] + 1;
                que.push(v);
            }
        }
        
        return std::max_element(dis.begin(), dis.end()) - dis.begin();
    };
    
    int u = bfs(0);
    int v = bfs(u);
    
    int r = v, diam = dis[v];
    for (int i = 0; i < diam / 2; i++) {
        r = parent[r];
    }
    
    std::vector<int> len;
    
    std::function<int(int, int)> dfs = [&](int u, int p) {
        
        int res = 0;
        
        for (auto v : e[u]) {
            if (v == p) {
                continue;
            }
            
            int x = dfs(v, u);
            if (p == -1) {
                len.push_back(x);
            } else if (res == 0) {
                res = x;
            } else if (res != x) {
                std::cout << "-1\n";
                std::exit(0);
            }
        }
        
        return res + 1;
    };
    
    dfs(r, -1);
    
    std::sort(len.begin(), len.end());
    len.erase(std::unique(len.begin(), len.end()), len.end());
    
    if (len.size() > 2) {
        std::cout << "-1\n";
        return 0;
    }
    
    int ans = std::accumulate(len.begin(), len.end(), 0);
    while (ans % 2 == 0) {
        ans /= 2;
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
