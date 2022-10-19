// url:https://codeforces.com/contest/1515/problem/F
// time:2021-05-02 18:14:26
// name:F-PhoenixandEarthquake

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
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
    int n, m, x;
    std::cin >> n >> m >> x;
    std::vector<i64> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    i64 sum = std::accumulate(a.begin(), a.end(), 0ll);
    if (sum < i64(n - 1) * x) {
        std::cout << "NO\n";
        return 0;
    }
    DSU t(n);
    std::vector<std::vector<std::pair<int, int>>> e(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        e[u].emplace_back(v, i);
        e[v].emplace_back(u, i);
    }
    std::priority_queue<std::pair<i64, int>> h;
    for (int i = 0; i < n; i++) {
        h.emplace(a[i], i);
    }
    std::cout << "YES\n";
    for (int r = 0; r < n - 1; r++) {
        int u = h.top().second;
        h.pop();
        while (t.leader(u) != u) {
            u = h.top().second;
            h.pop();
        }
        while (t.same(u, e[u].back().first)) {
            e[u].pop_back();
        }
        std::cout << e[u].back().second + 1 << "\n";
        int v = e[u].back().first;
        v = t.leader(v);
        t.merge(u, v);
        a[u] += a[v] - x;
        h.emplace(a[u], u);
        if (e[u].size() < e[v].size()) {
            std::swap(e[u], e[v]);
        }
        e[u].insert(e[u].end(), e[v].begin(), e[v].end());
        e[v].clear();
    }
    return 0;
}
