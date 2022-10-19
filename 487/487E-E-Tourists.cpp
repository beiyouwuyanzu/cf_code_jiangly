// url:https://codeforces.com/contest/487/problem/E
// time:2021-06-24 21:59:06
// name:E-Tourists

#include <bits/stdc++.h>
using i64 = long long;
constexpr int inf = 1e9;
struct SegmentTree {
    int n;
    std::vector<int> info;
    SegmentTree(int n) : n(n), info(4 * n) {}
    void pull(int p) {
        info[p] = std::min(info[2 * p], info[2 * p + 1]);
    }
    void modify(int p, int l, int r, int x, int v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int x, int v) {
        modify(1, 0, n, x, v);
    }
    int rangeMin(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return inf;
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return std::min(rangeMin(2 * p, l, m, x, y), rangeMin(2 * p + 1, m, r, x, y));
    }
    int rangeMin(int l, int r) {
        return rangeMin(1, 0, n, l, r);
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<int> w(n);
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    std::vector<std::vector<int>> e(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    int cnt = 0;
    std::vector<std::vector<int>> e1(n);
    std::vector<int> dfn(n, -1), low(n);
    int timeStamp = 0;
    std::vector<int> stk;
    std::function<void(int)> tarjan = [&](int u) {
        dfn[u] = low[u] = timeStamp++;
        stk.push_back(u);
        for (auto v : e[u]) {
            if (dfn[v] == -1) {
                tarjan(v);
                low[u] = std::min(low[u], low[v]);
                if (low[v] == dfn[u]) {
                    int x;
                    e1.push_back({});
                    do {
                        x = stk.back();
                        stk.pop_back();
                        e1[n + cnt].push_back(x);
                    } while (x != v);
                    e1[u].push_back(n + cnt);
                    cnt++;
                }
            } else {
                low[u] = std::min(low[u], dfn[v]);
            }
        }
    };
    tarjan(0);
    e = std::move(e1);
    std::vector<std::multiset<int>> s(cnt);
    int N = n + cnt;
    std::vector<int> in(N), dep(N), top(N), siz(N), parent(N);
    parent[0] = -1;
    std::function<void(int)> dfs1 = [&](int u) {
        siz[u] = 1;
        for (auto &v : e[u]) {
            dep[v] = dep[u] + 1;
            parent[v] = u;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[e[u][0]]) {
                std::swap(v, e[u][0]);
            }
        }
    };
    timeStamp = 0;
    dfs1(0);
    std::function<void(int)> dfs2 = [&](int u) {
        in[u] = timeStamp++;
        for (auto v : e[u]) {
            top[v] = v == e[u][0] ? top[u] : v;
            dfs2(v);
        }
    };
    dfs2(0);
    for (int i = 1; i < n; i++) {
        s[parent[i] - n].insert(w[i]);
    }
    SegmentTree t(N);
    for (int i = 0; i < n; i++) {
        t.modify(in[i], w[i]);
    }
    for (int i = 0; i < cnt; i++) {
        t.modify(in[n + i], *s[i].begin());
    }
    auto pathMin = [&](int u, int v) {
        int ans = inf;
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) {
                std::swap(u, v);
            }
            ans = std::min(ans, t.rangeMin(in[top[u]], in[u] + 1));
            u = parent[top[u]];
        }
        if (dep[u] > dep[v]) {
            std::swap(u, v);
        }
        ans = std::min(ans, t.rangeMin(in[u], in[v] + 1));
        return ans;
    };
    auto lca = [&](int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) {
                std::swap(u, v);
            }
            u = parent[top[u]];
        }
        if (dep[u] > dep[v]) {
            std::swap(u, v);
        }
        return u;
    };
    while (q--) {
        char op;
        int x, y;
        std::cin >> op >> x >> y;
        if (op == 'A') {
            x--;
            y--;
            int ans = pathMin(x, y);
            int l = lca(x, y);
            if (l >= n) {
                ans = std::min(ans, w[parent[l]]);
            }
            std::cout << ans << "\n";
        } else {
            x--;
            if (x != 0) {
                int p = parent[x] - n;
                s[p].erase(s[p].find(w[x]));
                s[p].insert(y);
                t.modify(in[p + n], *s[p].begin());
            }
            w[x] = y;
            t.modify(in[x], y);
        }
    }
    return 0;
}
