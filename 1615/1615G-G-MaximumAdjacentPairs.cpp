//url:https://codeforces.com/contest/1615/problem/G
//time:2021-12-24 20:35:13
//name:G-MaximumAdjacentPairs

#include <bits/stdc++.h>

using i64 = long long;

struct Graph {
    int n;
    std::vector<std::vector<int>> e;
    Graph(int n) : n(n), e(n) {}
    void addEdge(int u, int v) {
        e[u].push_back(v);
        e[v].push_back(u);
    }
    std::vector<int> findMatching() {
        std::vector<int> match(n, -1), vis(n), link(n), f(n), dep(n);
        
        // disjoint set union
        auto find = [&](int u) {
            while (f[u] != u)
                u = f[u] = f[f[u]];
            return u;
        };
        
        auto lca = [&](int u, int v) {
            u = find(u);
            v = find(v);
            while (u != v) {
                if (dep[u] < dep[v])
                    std::swap(u, v);
                u = find(link[match[u]]);
            }
            return u;
        };
        
        std::queue<int> que;
        auto blossom = [&](int u, int v, int p) {
            while (find(u) != p) {
                link[u] = v;
                v = match[u];
                if (vis[v] == 0) {
                    vis[v] = 1;
                    que.push(v);
                }
                f[u] = f[v] = p;
                u = link[v];
            }
        };
        
        // find an augmenting path starting from u and augment (if exist)
        auto augment = [&](int u) {
            
            while (!que.empty())
                que.pop();
            
            std::iota(f.begin(), f.end(), 0);
            
            // vis = 0 corresponds to inner vertices, vis = 1 corresponds to outer vertices
            std::fill(vis.begin(), vis.end(), -1);
            
            que.push(u);
            vis[u] = 1;
            dep[u] = 0;
        
            while (!que.empty()){
                int u = que.front();
                que.pop();
                for (auto v : e[u]) {
                    if (vis[v] == -1) {
                        
                        vis[v] = 0;
                        link[v] = u;
                        dep[v] = dep[u] + 1;
                        
                        // found an augmenting path
                        if (match[v] == -1) {
                            for (int x = v, y = u, temp; y != -1; x = temp, y = x == -1 ? -1 : link[x]) {
                                temp = match[y];
                                match[x] = y;
                                match[y] = x;
                            }
                            return;
                        }
                        
                        vis[match[v]] = 1;
                        dep[match[v]] = dep[u] + 2;
                        que.push(match[v]);
                        
                    } else if (vis[v] == 1 && find(v) != find(u)) {
                        // found a blossom
                        int p = lca(u, v);
                        blossom(u, v, p);
                        blossom(v, u, p);
                    }
                }
            }
            
        };
        
        // find a maximal matching greedily (decrease constant)
        auto greedy = [&]() {
            
            for (int u = 0; u < n; ++u) {
                if (match[u] != -1)
                    continue;
                for (auto v : e[u]) {
                    if (match[v] == -1) {
                        match[u] = v;
                        match[v] = u;
                        break;
                    }
                }
            }
        };
        
        greedy();
        
        for (int u = 0; u < n; ++u)
            if (match[u] == -1)
                augment(u);
        
        return match;
    }
};

struct Flow {
    static constexpr int INF = 1e9;
    int n;
    struct Edge {
        int to, cap;
        Edge(int to, int cap) : to(to), cap(cap) {}
    };
    std::vector<Edge> e;
    std::vector<std::vector<int>> g;
    std::vector<int> cur, h;
    Flow(int n) : n(n), g(n) {}
    bool bfs(int s, int t) {
        h.assign(n, -1);
        std::queue<int> que;
        h[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int i : g[u]) {
                int v = e[i].to;
                int c = e[i].cap;
                if (c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t)
                        return true;
                    que.push(v);
                }
            }
        }
        return false;
    }
    int dfs(int u, int t, int f) {
        if (u == t)
            return f;
        int r = f;
        for (int &i = cur[u]; i < int(g[u].size()); ++i) {
            int j = g[u][i];
            int v = e[j].to;
            int c = e[j].cap;
            if (c > 0 && h[v] == h[u] + 1) {
                int a = dfs(v, t, std::min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (r == 0)
                    return f;
            }
        }
        return f - r;
    }
    void addEdge(int u, int v, int c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }
    int maxFlow(int s, int t) {
        int ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, INF);
        }
        return ans;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
    }
    
    const int N = std::min(n, 600);
    
    if (a == std::vector(n, -1)) {
        for (int i = 0; i < n; i++) {
            a[i] = i / 2;
        }
    } else {
        std::vector<bool> vis(n);
        std::vector<int> v;
        for (int i = 0; i < n; i++) {
            if (a[i] != -1) {
                vis[a[i]] = true;
                v.push_back(i);
            }
        }
        
        if (v[0] % 2 == 1) {
            a[v[0] - 1] = a[v[0]];
        }
        if ((n - 1 - v.back()) % 2 == 1) {
            a[v.back() + 1] = a[v.back()];
        }
        
        int x = 0;
        for (int i = 0; a[i] == -1; i += 2) {
            while (vis[x]) {
                x++;
            }
            a[i] = a[i + 1] = x++;
        }
        for (int i = n - 1; a[i] == -1; i -= 2) {
            while (vis[x]) {
                x++;
            }
            a[i] = a[i - 1] = x++;
        }
        
        std::vector<bool> get(n);
        for (int i = 0; i < n - 1; i++) {
            if (a[i] != -1 && a[i] == a[i + 1]) {
                get[a[i]] = true;
            }
        }
        
        std::vector<std::pair<int, int>> edge1, edge2;
        std::vector<std::vector<int>> adj(N);
        std::vector<int> belong(N, -1);
        
        for (int i = 0; i + 1 < int(v.size()); i++) {
            int len = v[i + 1] - v[i] - 1;
            
            if (len % 2 == 0) {
                continue;
            }
            
            int l = a[v[i]], r = a[v[i + 1]];
            if (get[l]) {
                l = r;
            }
            if (get[r]) {
                r = l;
            }
            adj[l].push_back(r);
            adj[r].push_back(l);
            edge1.emplace_back(v[i], v[i + 1]);
        }
        
        std::vector<bool> good;
        
        int com = 0;
        for (int s = 0; s < N; s++) {
            if (belong[s] != -1) {
                continue;
            }
            
            std::queue<int> q;
            belong[s] = com;
            q.push(s);
            int E = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                E += adj[u].size();
                E -= 2;
                for (auto v : adj[u]) {
                    if (belong[v] == -1) {
                        belong[v] = com;
                        q.push(v);
                    }
                }
            }
            com++;
            if (E == -2) {
                good.push_back(true);
            } else {
                good.push_back(false);
            }
        }
        
        Graph g(com);
        
        for (int i = 0; i + 1 < int(v.size()); i++) {
            int len = v[i + 1] - v[i] - 1;
            
            if (len % 2 == 1 || len == 0) {
                continue;
            }
            
            int l = a[v[i]], r = a[v[i + 1]];
            if (!good[belong[l]] || !good[belong[r]] || get[l] || get[r] || belong[l] == belong[r]) {
                for (int j = v[i] + 1; j < v[i + 1]; j += 2) {
                    while (vis[x]) {
                        x++;
                    }
                    a[j] = a[j + 1] = x++;
                }
                continue;
            }
            edge2.emplace_back(v[i], v[i + 1]);
            g.addEdge(belong[l], belong[r]);
        }
        
        auto match = g.findMatching();
        
        for (auto [l, r] : edge2) {
            int x = a[l], y = a[r];
            if (match[belong[x]] == belong[y]) {
                match[belong[x]] = match[belong[y]] = -1;
                a[l + 1] = x;
                a[r - 1] = y;
                assert(!get[x]);
                assert(!get[y]);
                get[x] = get[y] = true;
            }
        }
        
        Flow flow(n + N + 2);
        const int source = n + N, sink = source + 1;
        
        for (int i = 0; i < N; i++) {
            flow.addEdge(i, sink, 1);
        }
        
        for (int i = 0; i < int(edge1.size()); i++) {
            auto [l, r] = edge1[i];
            int x = a[l], y = a[r];
            if (get[x]) {
                x = y;
            }
            if (get[y]) {
                y = x;
            }
            flow.addEdge(source, N + i, 1);
            flow.addEdge(N + i, x, 1);
            flow.addEdge(N + i, y, 1);
        }
        flow.maxFlow(source, sink);
        
        for (int i = 0; i < int(flow.e.size()); i += 2) {
            int u = flow.e[i ^ 1].to;
            int v = flow.e[i].to;
            
            if (N <= u && u < N + n && v < N && flow.e[i ^ 1].cap > 0) {
                int j = u - N;
                auto [l, r] = edge1[j];
                
                if (a[l] == v) {
                    a[l + 1] = v;
                } else {
                    a[r - 1] = v;
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            if (a[i] == -1) {
                if (a[i + 1] == -1) {
                    while (vis[x]) {
                        x++;
                    }
                    a[i] = a[i + 1] = x++;
                    i++;
                } else {
                    a[i] = a[i - 1];
                }
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        std::cout << a[i] + 1 << " \n"[i == n - 1];
    }
    
    return 0;
}

