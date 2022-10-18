//url:https://codeforces.com/contest/827/problem/D
//time:2021-03-31 15:25:27
//name:D-BestEdgeWeight

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
struct DSU {
    std::vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return leader(x) == leader(y); }
    bool merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[leader(x)]; }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> u(m), v(m), c(m);
    for (int i = 0; i < m; i++) {
        std::cin >> u[i] >> v[i] >> c[i];
        u[i]--;
        v[i]--;
    }
    std::vector<int> p(m);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j) {
        return c[i] < c[j];
    });
    DSU t(n);
    std::vector<std::vector<std::pair<int, int>>> e(n);
    std::vector<bool> vis(m);
    for (auto i : p) {
        if (t.merge(u[i], v[i])) {
            vis[i] = true;
            e[u[i]].emplace_back(v[i], i);
            e[v[i]].emplace_back(u[i], i);
        }
    }
    int lg = std::__lg(n);
    std::vector<std::vector<int>> parent(n, std::vector<int>(lg + 1, -1)), mx(n, std::vector<int>(lg + 1));
    std::vector<int> id(n, -1), dep(n);
    std::function<void(int)> dfs = [&](int u) {
        for (int i = 1; (1 << i) <= dep[u]; i++) {
            int p = parent[u][i - 1];
            parent[u][i] = parent[p][i - 1];
            mx[u][i] = std::max(mx[u][i - 1], mx[p][i - 1]);
        }
        for (auto [v, i] : e[u]) {
            if (v == parent[u][0]) {
                continue;
            }
            id[v] = i;
            parent[v][0] = u;
            mx[v][0] = c[i];
            dep[v] = dep[u] + 1;
            dfs(v);
        }
    };
    dfs(0);
    std::vector<int> ans(m, -1);
    auto query = [&](int u, int v) {
        int ans = 0;
        if (dep[u] < dep[v]) {
            std::swap(u, v);
        }
        for (int i = lg; i >= 0; i--) {
            if (dep[u] - (1 << i) >= dep[v]) {
                ans = std::max(ans, mx[u][i]);
                u = parent[u][i];
            }
        }
        if (u == v) {
            return ans;
        }
        for (int i = lg; i >= 0; i--) {
            if (dep[u] >= (1 << i) && parent[u][i] != parent[v][i]) {
                ans = std::max({ans, mx[u][i], mx[v][i]});
                u = parent[u][i];
                v = parent[v][i];
            }
        }
        return std::max({ans, mx[u][0], mx[v][0]});
    };
    t = DSU(n);
    for (auto i : p) {
        if (!vis[i]) {
            ans[i] = query(u[i], v[i]) - 1;
            int a = t.leader(u[i]);
            int b = t.leader(v[i]);
            while (a != b) {
                if (dep[a] < dep[b]) {
                    std::swap(a, b);
                }
                ans[id[a]] = c[i] - 1;
                t.merge(parent[a][0], a);
                a = t.leader(a);
            }
        }
    }
    for (int i = 0; i < m; i++) {
        std::cout << ans[i] << " \n"[i == m - 1];
    }
    return 0;
}

