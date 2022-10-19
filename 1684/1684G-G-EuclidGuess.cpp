// url:https://codeforces.com/contest/1684/problem/G
// time:2022-05-19 18:44:48
// name:G-EuclidGuess

#include <bits/stdc++.h>

using i64 = long long;
struct Flow {
    static constexpr int INF = 1e9;
    int n;
    struct Edge {
        int to, cap;
        Edge(int to, int cap) : to(to), cap(cap) {}
    };
    std::vector<Edge> e;
    std::vector<std::vector<int>> g;
    std::vector<int> cur, h;
    Flow(int n) : n(n), g(n) {}
    bool bfs(int s, int t) {
        h.assign(n, -1);
        std::queue<int> que;
        h[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int i : g[u]) {
                int v = e[i].to;
                int c = e[i].cap;
                if (c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t)
                        return true;
                    que.push(v);
                }
            }
        }
        return false;
    }
    int dfs(int u, int t, int f) {
        if (u == t)
            return f;
        int r = f;
        for (int &i = cur[u]; i < int(g[u].size()); ++i) {
            int j = g[u][i];
            int v = e[j].to;
            int c = e[j].cap;
            if (c > 0 && h[v] == h[u] + 1) {
                int a = dfs(v, t, std::min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (r == 0)
                    return f;
            }
        }
        return f - r;
    }
    void addEdge(int u, int v, int c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }
    int maxFlow(int s, int t) {
        int ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, INF);
        }
        return ans;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> t(n);
    for (int i = 0; i < n; i++) {
        std::cin >> t[i];
    }
    
    Flow flow(n + 2);
    int source = n, sink = n + 1;
    
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        if (3LL * t[i] > m) {
            count++;
            flow.addEdge(source, i, 1);
        } else {
            flow.addEdge(i, sink, 1);
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (3LL * t[i] > m) {
            for (int j = 0; j < n; j++) {
                if (3LL * t[j] <= m && t[i] % t[j] == 0 && 2LL * t[i] + t[j] <= m) {
                    flow.addEdge(i, j, 1);
                }
            }
        }
    }
    
    if (count != flow.maxFlow(source, sink)) {
        std::cout << "-1\n";
        return 0;
    }
    
    std::vector<bool> vis(n);
    std::vector<std::array<int, 2>> ans;
    for (int i = 2 * n; i < int(flow.e.size()); i += 2) {
        int u = flow.e[i + 1].to;
        int v = flow.e[i].to;
        int c = flow.e[i + 1].cap;
        
        if (c > 0) {
            vis[u] = vis[v] = true;
            ans.push_back({2 * t[u] + t[v], t[u] + t[v]});
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            ans.push_back({3 * t[i], 2 * t[i]});
        }
    }
    
    std::cout << ans.size() << "\n";
    for (auto [x, y] : ans) {
        std::cout << x << " " << y << "\n";
    }
    
    return 0;
}
