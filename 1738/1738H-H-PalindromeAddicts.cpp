//url:https://codeforces.com/contest/1738/problem/H
//time:2022-09-30 21:33:12
//name:H-PalindromeAddicts

#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1E6 + 100;

struct Node {
    int ch[26];
    int len;
    int link;
} t[N];

int cnt = 2;

struct Tree {
    int n;
    std::vector<int> siz, top, dep, parent, in, out;
    std::vector<std::vector<int>> adj;
    Tree(int n) : n(n), siz(n), top(n), dep(n), parent(n, -1), in(n), out(n), adj(n) {}
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void init(int root = 0) {
        top[root] = root;
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if (parent[u] != -1) {
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), parent[u]));
        }
        
        siz[u] = 1;
        for (auto &v : adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                std::swap(v, adj[u][0]);
            }
        }
    }
    int cur = 0;
    void dfs2(int u) {
        in[u] = cur++;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
};
template<class Info,
    class Merge = std::plus<Info>>
struct SegmentTree {
    const int n;
    const Merge merge;
    std::vector<Info> info;
    SegmentTree(int n) : n(n), merge(Merge()), info(4 << std::__lg(n)) {}
    SegmentTree(std::vector<Info> init) : SegmentTree(init.size()) {
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
    void modify(int p, int l, int r, int x, const Info &v) {
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
        return merge(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m, r, x, y));
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
};

struct Max {
    int x = -1;
};
Max operator+(const Max &a, const Max &b) {
    return {std::max(a.x, b.x)};
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    t[1].len = -1;
    t[0].link = 1;
    t[1].link = -1;
    
    int q;
    std::cin >> q;
    
    std::string s;
    
    std::vector<int> l(q), r(q);
    
    for (int i = 0, L = 0; i < q; i++) {
        std::string op;
        std::cin >> op;
        
        if (op == "push") {
            char c;
            std::cin >> c;
            s += c;
        } else {
            L++;
        }
        l[i] = L;
        r[i] = s.length();
    }
    
    // std::cerr << "s : " << s << "\n";
    
    auto add = [&](int p, int i) {
        while (i - t[p].len - 1 < 0 || s[i - t[p].len - 1] != s[i]) {
            p = t[p].link;
        }
        if (i - t[p].len - 1 < 0 || s[i - t[p].len - 1] != s[i]) {
            return p;
        }
        const int x = s[i] - 'a';
        if (!t[p].ch[x]) {
            int u = cnt++;
            t[u].len = t[p].len + 2;
            t[p].ch[x] = u;
            if (p == 1) {
                t[u].link = 0;
            } else {
                p = t[p].link;
                while (i - t[p].len - 1 < 0 || s[i - t[p].len - 1] != s[i]) {
                    p = t[p].link;
                }
                t[u].link = t[p].ch[x];
            }
            return u;
        }
        return t[p].ch[x];
    };
    
    const int n = s.length();
    int p = 0;
    for (int i = 0; i < n; i++) {
        p = add(p, i);
        // std::cerr << p << " " << t[p].len << " " << t[p].link << "\n";
    }
    
    Tree tree(cnt);
    for (int i = 0; i < cnt; i++) {
        if (i != 1) {
            tree.addEdge(t[i].link, i);
        }
    }
    tree.init(1);
    std::vector<int> ans(q);
    
    SegmentTree<Max> seg(cnt);
    std::vector<int> f(cnt, -1);
    
    int cur = 0;
    for (int i = 0; i < q; i++) {
        if (r[i] > cur) {
            while (cur - t[p].len - 1 < 0 || s[cur - t[p].len - 1] != s[cur]) {
                p = t[p].link;
            }
            p = t[p].ch[s[cur] - 'a'];
            while (t[p].len > r[i] - l[i]) {
                p = t[p].link;
            }
            if (seg.rangeQuery(tree.in[p], tree.out[p]).x < l[i] + t[p].len - 1) {
                ans[i] = 1;
            }
            if (cur > f[tree.in[p]]) {
                seg.modify(tree.in[p], {f[tree.in[p]] = cur});
            }
            cur++;
        }
    }
    
    for (int i = 0; i < cnt; i++) {
        seg.modify(i, {-1});
    }
    
    f.assign(cnt, -1);
    cur = n;
    while (cur > l[q - 1]) {
        cur--;
        while (cur + t[p].len + 1 >= n || s[cur] != s[cur + t[p].len + 1]) {
            p = t[p].link;
        }
        p = t[p].ch[s[cur] - 'a'];
        while (t[p].len > n - cur) {
            p = t[p].link;
        }
        // std::cerr << "p : " << p << "\n";
        if (n - 1 - cur > f[tree.in[p]]) {
            seg.modify(tree.in[p], {f[tree.in[p]] = n - 1 - cur});
        }
    }
    for (int i = q - 2; i >= 0; i--) {
        if (l[i] < cur) {
            cur--;
            while (cur + t[p].len + 1 >= n || s[cur] != s[cur + t[p].len + 1]) {
                p = t[p].link;
            }
            p = t[p].ch[s[cur] - 'a'];
            while (t[p].len > r[i] - l[i]) {
                p = t[p].link;
            }
            // if (i == 24) {
            //     std::cerr << n - 1 - seg.rangeQuery(tree.in[p], tree.out[p]).x << "\n";
            //     std::cerr << cur << "\n";
            // }
            if (n - 1 - seg.rangeQuery(tree.in[p], tree.out[p]).x > r[i] - t[p].len) {
                ans[i + 1] = -1;
            }
            // std::cerr << l[i] << " " << r[i] << " " << p << "\n";
            if (n - 1 - cur > f[tree.in[p]]) {
                // std::cerr << n - 1 - cur << "\n";
                seg.modify(tree.in[p], {f[tree.in[p]] = n - 1 - cur});
            }
        }
    }
    
    // for (int i = 0; i < q; i++) {
    //     std::cerr << l[i] << " " << r[i] << " " << node[i] << " " << t[node[i]].len << "\n";
    // }
    
    for (int i = 0; i < q; i++) {
        if (i > 0) {
            ans[i] += ans[i - 1];
        }
        // std::cerr << s.substr(l[i], r[i] - l[i]) << "\n";
        std::cout << ans[i] << "\n";
    }
    
    return 0;
}
