// url:https://codeforces.com/contest/704/problem/E
// time:2023-03-14 20:39:29
// name:E-IronMan

#include <bits/stdc++.h>

using i64 = long long;

struct HLD {
    int n;
    std::vector<int> siz, top, dep, parent, in, out, seq;
    std::vector<std::vector<int>> adj;
    int cur;
    
    HLD() {}
    HLD(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        siz.resize(n);
        top.resize(n);
        dep.resize(n);
        parent.resize(n);
        in.resize(n);
        out.resize(n);
        seq.resize(n);
        cur = 0;
        adj.assign(n, {});
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void work(int root = 0) {
        top[root] = root;
        dep[root] = 0;
        parent[root] = -1;
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
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
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
    
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    
    int jump(int u, int k) {
        if (dep[u] < k) {
            return -1;
        }
        
        int d = dep[u] - k;
        
        while (dep[top[u]] > d) {
            u = parent[top[u]];
        }
        
        return seq[in[u] - dep[u] + d];
    }
    
    bool isAncester(int u, int v) {
        return in[u] <= in[v] && in[v] < out[u];
    }
    
    int rootedChild(int u, int v) {
        if (u == v) {
            return u;
        }
        if (!isAncester(u, v)) {
            return parent[u];
        }
        auto it = std::upper_bound(adj[u].begin(), adj[u].end(), v, [&](int x, int y) {
            return in[x] < in[y];
        }) - 1;
        return *it;
    }
    
    int rootedSize(int u, int v) {
        if (u == v) {
            return n;
        }
        if (!isAncester(v, u)) {
            return siz[v];
        }
        return n - siz[rootedChild(v, u)];
    }
    
    int rootedLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};

struct Line {
    double l;
    double r;
    double k;
    double b;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    HLD t(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        t.addEdge(u, v);
    }
    t.work();
    
    std::vector<std::vector<Line>> lines(n);
    
    for (int i = 0; i < m; i++) {
        int s, c, u, v;
        std::cin >> s >> c >> u >> v;
        u--, v--;
        
        int d = t.dist(u, v);
        int du = 0, dv = d;
        
        while (t.top[u] != t.top[v]) {
            if (t.dep[t.top[u]] > t.dep[t.top[v]]) {
                lines[t.top[u]].push_back({s + 1. * du / c, s + 1. * (du + t.dep[u] - t.dep[t.top[u]] + 1) / c
                    , -c, t.dep[u] + du + c * s});
                du += t.dep[u] - t.dep[t.top[u]] + 1;
                u = t.parent[t.top[u]];
            } else {
                dv -= t.dep[v] - t.dep[t.top[v]] + 1;
                lines[t.top[v]].push_back({s + 1. * dv / c, s + 1. * (dv + t.dep[v] - t.dep[t.top[v]] + 1) / c
                    , c, t.dep[t.top[v]] - 1 - dv - c * s});
                v = t.parent[t.top[v]];
            }
        }
        if (t.dep[u] <= t.dep[v]) {
            lines[t.top[v]].push_back({s + 1. * du / c, s + 1. * dv / c
                    , c, t.dep[u] - du - c * s});
        } else {
            lines[t.top[u]].push_back({s + 1. * du / c, s + 1. * dv / c
                    , -c, t.dep[u] + du + c * s});
        }
    }
    
    double ans = -1;
    for (int i = 0; i < n; i++) {
        if (t.top[i] != i) {
            continue;
        }
        auto &L = lines[i];
        std::vector<std::tuple<double, int, int>> events;
        for (int j = 0; j < L.size(); j++) {
            events.emplace_back(L[j].l, 0, j);
            events.emplace_back(L[j].r, 1, j);
        }
        std::sort(events.begin(), events.end());
        
        double cur = 0;
        auto cmp = [&](int i, int j) {
            double a = L[i].k * cur + L[i].b;
            double b = L[j].k * cur + L[j].b;
            if (a != b) {
                return a < b;
            }
            return i < j;
        };
        
        auto updateAns = [&](double x) {
            if (ans < 0 || ans > x) {
                ans = x;
            }
        };
        
        auto update = [&](int i, int j) {
            double l = std::max(L[i].l, L[j].l);
            double a = L[i].k * l + L[i].b;
            double b = L[j].k * l + L[j].b;
            if (a == b) {
                updateAns(l);
                return;
            }
            double r = std::min(L[i].r, L[j].r);
            double c = L[i].k * r + L[i].b;
            double d = L[j].k * r + L[j].b;
            if (c == d) {
                updateAns(r);
                return;
            }
            if ((a > b) == (c > d)) {
                return;
            }
            double x = (L[i].b - L[j].b) / (L[j].k - L[i].k);
            updateAns(x);
        };
        
        std::set<int, decltype(cmp)> s(cmp);
        for (auto [x, t, i] : events) {
            cur = x;
            if (ans != -1 && x >= ans) {
                break;
            }
            if (t == 0) {
                auto it = s.insert(i).first;
                if (it != s.begin()) {
                    update(*std::prev(it), i);
                }
                it++;
                if (it != s.end()) {
                    update(*it, i);
                }
            } else {
                auto it = s.erase(s.find(i));
                if (it != s.begin() && it != s.end()) {
                    update(*std::prev(it), *it);
                }
            }
        }
    }
    
    if (ans < 0) {
        std::cout << -1 << "\n";
        return 0;
    }
    
    std::cout << std::fixed << std::setprecision(10);
    std::cout << ans << "\n";
    
    return 0;
}

