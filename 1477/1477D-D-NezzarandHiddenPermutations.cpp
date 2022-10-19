// url:https://codeforces.com/contest/1477/problem/D
// time:2021-01-28 18:54:12
// name:D-NezzarandHiddenPermutations

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
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> e(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        x--;
        y--;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    std::vector<std::vector<int>> e0(n);
    DSU t(n);
    for (int i = 0; i < n; i++) {
        std::sort(e[i].begin(), e[i].end());
        int x = (i == 0);
        int j = 0;
        while (j < int(e[i].size()) && e[i][j] == x) {
            j++;
            x++;
            if (i == j) {
                x++;
            }
        }
        if (x < n && t.merge(x, i)) {
            e0[i].push_back(x);
            e0[x].push_back(i);
        }
    }
    int cur = 0;
    std::vector<int> p(n), q(n);
    std::vector<std::vector<int>> a(n);
    std::function<bool(int, int)> dfs = [&](int u, int p) {
        for (auto v : e0[u]) {
            if (v == p) {
                continue;
            }
            if (dfs(v, u)) {
                a[u].push_back(v);
            }
        }
        if (p == -1 && a[u].empty()) {
            a[e0[u][0]].push_back(u);
        }
        return a[u].empty();
    };
    for (int i = 0; i < n; i++) {
        if (t.leader(i) != i) {
            continue;
        }
        if (e0[i].empty()) {
            p[i] = q[i] = cur++;
            continue;
        }
        dfs(i, -1);
    }
    for (int i = 0; i < n; i++) {
        if (a[i].empty()) {
            continue;
        }
        p[i] = cur;
        for (auto v : a[i]) {
            q[v] = cur++;
            p[v] = cur;
        }
        q[i] = cur++;
    }
    for (int i = 0; i < n; i++) {
        std::cout << p[i] + 1 << " \n"[i == n - 1];
    }
    for (int i = 0; i < n; i++) {
        std::cout << q[i] + 1 << " \n"[i == n - 1];
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
