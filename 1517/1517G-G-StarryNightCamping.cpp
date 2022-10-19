// url:https://codeforces.com/contest/1517/problem/G
// time:2021-04-23 20:09:17
// name:G-StarryNightCamping

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
struct Flow {
    static constexpr i64 INF = 1e18;
    int n;
    struct Edge {
        int to;
        i64 cap;
        Edge(int to, i64 cap) : to(to), cap(cap) {}
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
    i64 dfs(int u, int t, i64 f) {
        if (u == t)
            return f;
        i64 r = f;
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
    void addEdge(int u, int v, i64 c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }
    i64 maxFlow(int s, int t) {
        i64 ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, INF);
        }
        return ans;
    }
};
constexpr i64 inf = 1e14;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> x(n), y(n), w(n);
    std::map<std::pair<int, int>, int> id;
    i64 tot = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i] >> w[i];
        id[{x[i], y[i]}] = i;
        tot += w[i];
    }
    Flow g(2 * n + 2);
    int S = 2 * n, T = S + 1;
    for (int i = 0; i < n; i++) {
        g.addEdge(i, i + n, w[i]);
        if (x[i] % 2 != 0 && y[i] % 2 == 0) {
            g.addEdge(S, i, inf);
            for (auto X : {x[i] - 1, x[i] + 1}) {
                if (id.count({X, y[i]})) {
                    int v = id[{X, y[i]}];
                    g.addEdge(i + n, v, inf);
                }
            }
        } else if (x[i] % 2 == 0 && y[i] % 2 == 0) {
            for (auto Y : {y[i] - 1, y[i] + 1}) {
                if (id.count({x[i], Y})) {
                    int v = id[{x[i], Y}];
                    g.addEdge(i + n, v, inf);
                }
            }
        } else if (x[i] % 2 == 0 && y[i] % 2 != 0) {
            for (auto X : {x[i] - 1, x[i] + 1}) {
                if (id.count({X, y[i]})) {
                    int v = id[{X, y[i]}];
                    g.addEdge(i + n, v, inf);
                }
            }
        } else {
            g.addEdge(i + n, T, inf);
        }
    }
    std::cout << tot - g.maxFlow(S, T) << "\n";
    return 0;
}

