// url:https://codeforces.com/contest/1662/problem/J
// time:2022-04-24 18:19:06
// name:J-TrainingCamp

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

constexpr int inf = 1E9;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector a(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
            a[i][j]--;
        }
    }
    
    std::vector c(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> c[i][j];
        }
    }
    
    Flow flow(n * n * 2 + 2);
    int source = n * n * 2, sink = n * n * 2 + 1;
    int tot = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tot += n + c[i][j];
            flow.addEdge(source, i * n + j, n + c[i][j]);
            flow.addEdge(n * n + i * n + j, sink, n + c[i][j]);
            flow.addEdge(n * n + i * n + j, i * n + j, inf);
        }
    }
    for (int i = 0; i < n; i++) {
        std::vector<int> q(n);
        for (int j = 0; j < n; j++) {
            q[a[i][j]] = j;
        }
        for (int j = 0; j < n - 1; j++) {
            flow.addEdge(i * n + q[j], n * n + i * n + q[j + 1], inf);
        }
    }
    for (int i = 0; i < n; i++) {
        std::vector<int> q(n);
        for (int j = 0; j < n; j++) {
            q[a[j][i]] = j;
        }
        for (int j = 0; j < n - 1; j++) {
            flow.addEdge(q[j] * n + i, n * n + q[j + 1] * n + i, inf);
        }
    }
    
    int ans = tot - flow.maxFlow(source, sink) - n * n;
    
    std::cout << ans << "\n";
    
    return 0;
}
