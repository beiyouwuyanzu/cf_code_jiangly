// url:https://codeforces.com/contest/1525/problem/F
// time:2022-06-27 11:11:21
// name:F-GoblinsAndGnomes

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

constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, k;
    std::cin >> n >> m >> k;
    
    std::vector<int> u(m), v(m);
    for (int i = 0; i < m; i++) {
        std::cin >> u[i] >> v[i];
        u[i]--;
        v[i]--;
    }
    
    auto get = [&](auto used) {
        Flow g(2 * n + 2);
        const int s = 2 * n, t = s + 1;
        for (int i = 0; i < n; i++) {
            if (used[i]) {
                g.addEdge(s, i, 1);
            }
            if (used[i + n]) {
                g.addEdge(i + n, t, 1);
            }
        }
        for (int i = 0; i < m; i++) {
            g.addEdge(u[i], v[i] + n, 1);
        }
        return g.maxFlow(s, t);
    };
    
    std::vector<bool> used(2 * n, true);
    int M = get(used);
    
    std::vector<int> op;
    
    for (int t = 0; t < M; t++) {
        for (int i = 0; i < 2 * n; i++) {
            if (used[i]) {
                used[i] = false;
                if (get(used) == M - t - 1) {
                    op.push_back(i);
                    break;
                }
                used[i] = true;
            }
        }
    }
    
    for (int i = 0; i < M; i++) {
        if (op[i] < n) {
            op[i]++;
        } else {
            op[i] = -(op[i] - n + 1);
        }
    }
    
    std::vector<int> x(k), y(k);
    for (int i = 0; i < k; i++) {
        std::cin >> x[i] >> y[i];
    }
    
    std::vector dp(k + 1, std::vector(M + 1, std::array{-inf, -1LL}));
    dp[0][M][0] = 0;
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j <= M; j++) {
            for (int l = 0; l <= j && l <= n - i - 1; l++) {
                dp[i][l] = std::max(dp[i][l], std::array{dp[i - 1][j][0] + std::max(0LL, x[i - 1] - 1LL * y[i - 1] * (j - l)), 1LL * j});
            }
        }
    }
    
    std::vector<int> cnt(k), ans;
    for (int i = k, l = std::min(M, n - k - 1); i > 0; i--) {
        cnt[i - 1] = dp[i][l][1] - l;
        l = dp[i][l][1];
    }
    int cur = 0;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < cnt[i]; j++) {
            ans.push_back(op[cur]);
            cur++;
        }
        ans.push_back(0);
    }
    
    std::cout << ans.size() << "\n";
    for (int i = 0; i < int(ans.size()); i++) {
        std::cout << ans[i] << " \n"[i == int(ans.size()) - 1];
    }
    
    return 0;
}

