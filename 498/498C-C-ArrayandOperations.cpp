// url:https://codeforces.com/contest/498/problem/C
// time:2021-06-21 21:46:10
// name:C-ArrayandOperations

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
                auto [v, c] = e[i];
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
            auto [v, c] = e[j];
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
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::vector<std::vector<int>> p(n);
    std::vector<int> b(n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        b[i] = sum;
        int x = a[i];
        for (int j = 2; j * j <= x; j++) {
            while (x % j == 0) {
                p[i].push_back(j);
                x /= j;
            }
        }
        if (x > 1) {
            p[i].push_back(x);
        }
        sum += p[i].size();
    }
    const int S = sum, T = sum + 1;
    Flow g(sum + 2);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < int(p[i].size()); j++) {
            if (i % 2 == 0) {
                g.addEdge(S, b[i] + j, 1);
            } else {
                g.addEdge(b[i] + j, T, 1);
            }
        }
    }
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        if (u % 2 != 0) {
            std::swap(u, v);
        }
        for (int i = 0; i < int(p[u].size()); i++) {
            for (int j = 0; j < int(p[v].size()); j++) {
                if (p[u][i] == p[v][j]) {
                    g.addEdge(b[u] + i, b[v] + j, 1);
                }
            }
        }
    }
    std::cout << g.maxFlow(S, T) << "\n";
    return 0;
}
