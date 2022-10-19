// url:https://codeforces.com/contest/1617/problem/E
// time:2021-12-17 05:22:47
// name:E-ChristmasChocolates

#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    std::vector<int> v{0};
    
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        for (int x = a[i]; x; x = (1 << std::__lg(2 * x - 1)) - x) {
            v.push_back(x);
        }
    }
    
    std::sort(v.begin(), v.end());
    
    v.erase(std::unique(v.begin(), v.end()), v.end());
    
    int N = v.size();
    std::vector<std::vector<int>> adj(N);
    
    for (int i = 1; i < N; i++) {
        int x = v[i];
        int j = std::lower_bound(v.begin(), v.end(), (1 << std::__lg(2 * x - 1)) - x) - v.begin();
        
        adj[j].push_back(i);
        adj[i].push_back(j);
    }
    
    std::vector<int> dis(N, -1);
    auto bfs = [&](int s) {
        dis.assign(N, -1);
        std::queue<int> q;
        q.push(s);
        dis[s] = 0;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (auto v : adj[u]) {
                if (dis[v] == -1) {
                    dis[v] = dis[u] + 1;
                    q.push(v);
                }
            }
        }
        
        int j = -1, d = -1;
        for (auto x : a) {
            int k = std::lower_bound(v.begin(), v.end(), x) - v.begin();
            
            if (dis[k] > d) {
                d = dis[k];
                j = k;
            }
        }
        
        return j;
    };
    
    int x = bfs(0);
    int y = bfs(x);
    
    int j1 = std::find(a.begin(), a.end(), v[x]) - a.begin();
    int j2 = std::find(a.begin(), a.end(), v[y]) - a.begin();
    
    if (j1 == j2) {
        j2++;
    }
    
    std::cout << j1 + 1 << " " << j2 + 1 << " " << dis[y] << "\n";
    
    return 0;
}
