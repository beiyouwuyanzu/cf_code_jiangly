// url:https://codeforces.com/contest/506/problem/D
// time:2021-06-24 16:35:34
// name:D-Mr.Kitayuta'sColorfulGraph

#include <bits/stdc++.h>
using i64 = long long;
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
    std::vector<std::vector<std::pair<int, int>>> edges(m);
    std::vector<std::vector<int>> col(n);
    std::vector<std::vector<int>> ver(m);
    for (int i = 0; i < m; i++) {
        int u, v, c;
        std::cin >> u >> v >> c;
        c--;
        u--;
        v--;
        edges[c].emplace_back(u, v);
        col[u].push_back(c);
        col[v].push_back(c);
        ver[c].push_back(u);
        ver[c].push_back(v);
    }
    for (int i = 0; i < m; i++) {
        std::sort(ver[i].begin(), ver[i].end());
        ver[i].erase(std::unique(ver[i].begin(), ver[i].end()), ver[i].end());
    }
    for (int i = 0; i < n; i++) {
        std::sort(col[i].begin(), col[i].end());
        col[i].erase(std::unique(col[i].begin(), col[i].end()), col[i].end());
    }
    int q;
    std::cin >> q;
    std::map<std::pair<int, int>, int> id;
    std::vector<int> last(q, -1);
    std::vector<std::vector<std::pair<int, int>>> queries(n);
    for (int i = 0; i < q; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        if (u > v) {
            std::swap(u, v);
        }
        if (id.count({u, v})) {
            last[i] = id[{u, v}];
            continue;
        }
        id[{u, v}] = i;
        if (col[u].size() > col[v].size()) {
            std::swap(u, v);
        }
        queries[u].emplace_back(v, i);
    }
    DSU t(n);
    std::vector<int> ans(q);
    for (int c = 0; c < m; c++) {
        for (auto [u, v] : edges[c]) {
            t.merge(u, v);
        }
        for (auto u : ver[c]) {
            for (auto [v, i] : queries[u]) {
                ans[i] += t.same(u, v);
            }
        }
        for (auto [u, v] : edges[c]) {
            t.f[u] = u;
            t.f[v] = v;
        }
    }
    for (int i = 0; i < q; i++) {
        if (last[i] != -1) {
            ans[i] = ans[last[i]];
        }
        std::cout << ans[i] << "\n";
    }
    return 0;
}
