//url:https://codeforces.com/contest/1555/problem/F
//time:2022-06-22 17:18:32
//name:F-GoodGraph

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

constexpr int inf = 1E9;

struct Max {
    int x;
    Max(int x = -inf) : x(x) {}
};

Max operator+(const Max &a, const Max &b) {
    return std::max(a.x, b.x);
}

void apply(Max &a, const Max &b) {
    a.x = std::max(a.x, b.x);
}

template<class Info, class Tag,
    class Merge = std::plus<Info>>
struct LazySegmentTree {
    const int n;
    const Merge merge;
    std::vector<Info> info;
    std::vector<Tag> tag;
    LazySegmentTree(int n) : n(n), merge(Merge()), info(4 << std::__lg(n)), tag(4 << std::__lg(n)) {}
    LazySegmentTree(std::vector<Info> init) : LazySegmentTree(init.size()) {
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = merge(info[2 * p], info[2 * p + 1]);
    }
    void apply(int p, const Tag &v) {
        ::apply(info[p], v);
        ::apply(tag[p], v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return merge(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m, r, x, y));
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n, l, r, v);
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<std::vector<std::array<int, 2>>> adj(n);
    std::vector<int> u(q), v(q), x(q);
    for (int i = 0; i < q; i++) {
        std::cin >> u[i] >> v[i] >> x[i];
        u[i]--;
        v[i]--;
    }
    std::vector<bool> ans(q);
    
    DSU dsu(n);
    
    for (int i = 0; i < q; i++) {
        if (dsu.merge(u[i], v[i])) {
            ans[i] = true;
            adj[u[i]].push_back({v[i], x[i]});
            adj[v[i]].push_back({u[i], x[i]});
        }
    }
    
    LazySegmentTree<Max, Max> seg(n);
    
    int cnt = 0;
    std::vector<int> in(n, -1), out(n), p(n, -1), dep(n), w(n), a(n);
    
    std::function<void(int)> dfs = [&](int u) {
        in[u] = cnt++;
        a[in[u]] = u;
        for (auto [v, x] : adj[u]) {
            if (in[v] != -1) {
                continue;
            }
            dep[v] = dep[u] + 1;
            p[v] = u;
            w[v] = w[u] ^ x;
            dfs(v);
        }
        out[u] = cnt;
    };
    
    for (int i = 0; i < n; i++) {
        if (in[i] == -1) {
            dfs(i);
        }
    }
    
    for (int i = 0; i < q; i++) {
        if (ans[i]) {
            continue;
        }
        if ((x[i] ^ w[u[i]] ^ w[v[i]]) == 0) {
            continue;
        }
        
        int x = std::max(seg.rangeQuery(in[u[i]], in[u[i]] + 1).x, seg.rangeQuery(in[v[i]], in[v[i]] + 1).x);
        
        if (x < 0 || (in[a[x]] <= in[u[i]] && in[u[i]] < out[a[x]] && in[a[x]] <= in[v[i]] && in[v[i]] < out[a[x]])) {
            ans[i] = true;
            int x = u[i];
            int y = v[i];
            while (x != y) {
                if (dep[x] < dep[y]) {
                    std::swap(x, y);
                }
                seg.rangeApply(in[x], out[x], in[x]);
                x = p[x];
            }
        }
    }
    
    for (int i = 0; i < q; i++) {
        std::cout << (ans[i] ? "YES" : "NO") << "\n";
    }
    
    return 0;
}

