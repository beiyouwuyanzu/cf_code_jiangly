// url:https://codeforces.com/contest/1682/problem/E
// time:2022-05-22 18:34:46
// name:E-UnorderedSwaps

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
        p[i]--;
    }
    
    std::vector<std::vector<int>> adj(n);
    std::map<std::array<int, 2>, int> id;
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        id[{u, v}] = id[{v, u}] = i;
    }
    
    std::vector<int> vis(n, -1);
    for (int i = 0; i < n; i++) {
        if (vis[i] != -1) {
            continue;
        }
        
        std::vector<int> a;
        int k = 0;
        for (int j = i; vis[j] == -1; j = p[j]) {
            vis[j] = k++;
            a.push_back(j);
        }
        for (auto x : a) {
            std::sort(adj[x].begin(), adj[x].end(), [&](int i, int j) {
                return (vis[i] - vis[x] + k) % k < (vis[j] - vis[x] + k) % k;
            });
        }
    }
    
    std::vector<int> cur(n);
    
    std::function<void(int)> check = [&](int x) {
        if (cur[x] == int(adj[x].size())) {
            return;
        }
        int y = adj[x][cur[x]];
        if (adj[y][cur[y]] != x) {
            return;
        }
        std::cout << id[{x, y}] + 1 << " ";
        cur[x]++;
        cur[y]++;
        check(x);
        check(y);
    };
    for (int i = 0; i < n; i++) {
        check(i);
    }
    std::cout << "\n";
    
    return 0;
}

