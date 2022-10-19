// url:https://codeforces.com/contest/1479/problem/D
// time:2021-02-07 19:07:19
// name:D-OddMineralResource

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
struct SegTree {
    u64 h;
    SegTree *lc, *rc;
};
SegTree *null = new SegTree;
SegTree *newSegTree() {
    SegTree *t = new SegTree;
    *t = *null;
    return t;
}
int n;
std::vector<SegTree *> tree;
std::vector<int> sz, top, dep, parent, a;
std::vector<std::vector<int>> e;
std::vector<u64> w;
SegTree *modify(SegTree *t, int l, int r, int x) {
    SegTree *nt = newSegTree();
    *nt = *t;
    nt->h ^= w[x];
    if (r - l == 1) {
        return nt;
    } else {
        int m = (l + r) / 2;
        if (x < m) {
            nt->lc = modify(nt->lc, l, m, x);
        } else {
            nt->rc = modify(nt->rc, m, r, x);
        }
        return nt;
    }
}
int query(SegTree *t1, SegTree *t2, SegTree *t3, SegTree *t4, int l, int r, int x, int y) {
    if ((t1->h ^ t2->h ^ t3->h ^ t4->h) == 0) {
        return -1;
    }
    if (l >= y || r <= x) {
        return -1;
    }
    if (r - l == 1) {
        return l;
    }
    int m = (l + r) / 2;
    int z = query(t1->lc, t2->lc, t3->lc, t4->lc, l, m, x, y);
    if (z == -1) {
        z = query(t1->rc, t2->rc, t3->rc, t4->rc, m, r, x, y);
    }
    return z;
}
void dfsSz(int u) {
    if (parent[u] != -1)
        e[u].erase(std::find(e[u].begin(), e[u].end(), parent[u]));
    tree[u] = modify(tree[u], 0, n, a[u]);
    sz[u] = 1;
    for (int &v : e[u]) {
        tree[v] = tree[u];
        parent[v] = u;
        dep[v] = dep[u] + 1;
        dfsSz(v);
        sz[u] += sz[v];
        if (sz[v] > sz[e[u][0]])
            std::swap(v, e[u][0]);
    }
}
void dfsHLD(int u) {
    for (int v : e[u]) {
        if (v == e[u][0]) {
            top[v] = top[u];
        } else {
            top[v] = v;
        }
        dfsHLD(v);
    }
}
int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] > dep[top[v]]) {
            u = parent[top[u]];
        } else {
            v = parent[top[v]];
        }
    }
    if (dep[u] < dep[v]) {
        return u;
    } else {
        return v;
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    null->h = 0;
    null->lc = null->rc = null;
    int q;
    std::cin >> n >> q;
    tree.resize(n, null);
    a.resize(n);
    w.resize(n);
    std::mt19937_64 gen(std::chrono::steady_clock::now().time_since_epoch().count());
    for (int i = 0; i < n; i++) {
        w[i] = gen();
    }
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
    }
    e.resize(n);
    sz.resize(n);
    top.resize(n);
    dep.resize(n);
    parent.resize(n);
    parent[0] = -1;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfsSz(0);
    dfsHLD(0);
    while (q--) {
        int u, v, l, r;
        std::cin >> u >> v >> l >> r;
        l--;
        u--;
        v--;
        int x = lca(u, v);
        x = query(tree[u], tree[v], tree[x], x == 0 ? null : tree[parent[x]], 0, n, l, r);
        if (x != -1) {
            x++;
        }
        std::cout << x << "\n";
    }
    return 0;
}
