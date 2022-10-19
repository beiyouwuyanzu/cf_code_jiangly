// url:https://codeforces.com/contest/725/problem/G
// time:2021-07-06 23:02:21
// name:G-MessagesonaTree

#include <bits/stdc++.h>

using i64 = long long;

struct SegmentTree {
    const int n;
    std::vector<int> info, tag;
    SegmentTree(int n) : n(n), info(4 << std::__lg(n)), tag(4 << std::__lg(n), -1) {}
    void pull(int p) {
        info[p] = std::max(info[2 * p], info[2 * p + 1]);
    }
    void modify(int p, int l, int r, int v) {
        tag[p] = v;
        info[p] = (r - l - 1) * 2 + v;
    }
    void push(int p, int l, int r) {
        if (tag[p] == -1) {
            return;
        }
        int m = (l + r) / 2;
        modify(2 * p, l, m, tag[p]);
        modify(2 * p + 1, m, r, tag[p] + (m - l) * 2);
        tag[p] = -1;
    }
    void rangeModify(int p, int l, int r, int x, int y, int v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            return modify(p, l, r, (l - x) * 2 + v);
        }
        int m = (l + r) / 2;
        push(p, l, r);
        rangeModify(2 * p, l, m, x, y, v);
        rangeModify(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeModify(int l, int r, int v) {
        rangeModify(1, 0, n, l, r, v);
    }
    int search(int p, int l, int r, int x, int y, int v) {
        if (l >= y || r <= x || info[p] <= v) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p, l, r);
        int res = search(2 * p + 1, m, r, x, y, v);
        if (res == -1) {
            res = search(2 * p, l, m, x, y, v);
        }
        return res;
    }
    int search(int l, int r, int v) {
        return search(1, 0, n, l, r, v);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    n++;
    
    std::vector<int> p(n);
    std::vector<std::vector<int>> e(n);
    p[0] = -1;
    for (int i = 1; i < n; i++) {
        std::cin >> p[i];
        e[p[i]].push_back(i);
    }
    
    std::vector<int> top(n), dep(n), siz(n), in(n), a(n);
    
    std::function<void(int)> dfs1 = [&](int u) {
        siz[u] = 1;
        for (auto &v : e[u]) {
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[e[u][0]]) {
                std::swap(v, e[u][0]);
            }
        }
    };
    dfs1(0);
    
    int tm = 0;
    std::function<void(int)> dfs2 = [&](int u) {
        a[tm] = u;
        in[u] = tm++;
        for (auto v : e[u]) {
            top[v] = (v == e[u][0] ? top[u] : v);
            dfs2(v);
        }
    };
    dfs2(0);
    
    SegmentTree seg(n);
    
    std::vector<int> x(m), t(m);
    
    for (int i = 0; i < m; i++) {
        std::cin >> x[i] >> t[i];
    }
    
    std::vector<int> q(m);
    std::iota(q.begin(), q.end(), 0);
    std::sort(q.begin(), q.end(), [&](int i, int j) {
        if (dep[x[i]] + t[i] != dep[x[j]] + t[j]) {
            return dep[x[i]] + t[i] < dep[x[j]] + t[j];
        } else {
            return x[i] < x[j];
        }
    });
    
    std::vector<int> ans(m);
    
    auto find = [&](int x, int t) {
        for (int i = x; i >= 0; i = p[top[i]]) {
            int res = seg.search(in[top[i]], in[i] + 1, t + dep[x]);
            if (res >= 0) {
                return a[res];
            }
        }
        return 0;
    };
    
    auto change = [&](int x, int u, int t) {
        t += dep[x] - 2 * dep[u];
        while (top[x] != top[u]) {
            seg.rangeModify(in[top[x]], in[x] + 1, t + 2 * dep[top[x]]);
            x = p[top[x]];
        }
        seg.rangeModify(in[u] + 1, in[x] + 1, t + 2 * dep[u] + 2);
    };
    
    for (auto i : q) {
        int u = find(x[i], t[i]);
        ans[i] = t[i] + 2 * (dep[x[i]] - dep[u]);
        change(x[i], u, t[i]);
    }
    
    for (int i = 0; i < m; i++) {
        std::cout << ans[i] << " \n"[i == m - 1];
    }
    
    return 0;
}
