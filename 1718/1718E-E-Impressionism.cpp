//url:https://codeforces.com/contest/1718/problem/E
//time:2022-09-28 11:42:12
//name:E-Impressionism

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
 
using i64 = long long;
 
struct Component {
    std::vector<std::array<int, 3>> edges;
    std::vector<int> px;
    std::vector<int> py;
};
 
bool operator<(const Component &a, const Component &b) {
    if (a.edges != b.edges) {
        return a.edges < b.edges;
    }
    if (a.px.size() != b.px.size()) {
        return a.px.size() < b.px.size();
    }
    return a.py.size() < b.py.size();
}
 
auto transpose(std::vector<std::vector<int>> a) {
    int n = a.size(), m = a[0].size();
    std::vector b(m, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            b[j][i] = a[i][j];
        }
    }
    return b;
}
 
auto work(std::vector<std::vector<int>> a) {
    int n = a.size(), m = a[0].size();
    
    std::vector<std::vector<std::array<int, 2>>> adj(n + m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j]) {
                adj[i].push_back({a[i][j], j + n});
                adj[j + n].push_back({a[i][j], i});
            }
        }
    }
    for (int i = 0; i < n + m; i++) {
        std::sort(adj[i].begin(), adj[i].end());
    }
    
    std::vector<Component> coms;
    std::vector<bool> vis(n + m);
    std::vector<int> id(n + m, -1);
    for (int s = 0; s < n + m; s++) {
        if (vis[s]) {
            continue;
        }
        
        Component com;
        
        std::vector<std::array<int, 3>> edges;
        std::vector<int> px, py;
        
        std::function<void(int)> dfs = [&](int x) {
            vis[x] = true;
            if (id[x] == -1) {
                if (x < n) {
                    id[x] = px.size();
                    px.push_back(x);
                } else {
                    id[x] = py.size();
                    py.push_back(x - n);
                }
            }
            for (auto [c, y] : adj[x]) {
                if (id[y] == -1) {
                    dfs(y);
                }
                edges.push_back({id[x], c, id[y]});
            }
        };
        
        dfs(s);
        
        com = {edges, px, py};
        
        const int nx = px.size();
        auto cand = px;
        for (int i = 1; i < nx; i++) {
            for (auto x : px) {
                id[x] = -1;
            }
            for (auto x : py) {
                id[x + n] = -1;
            }
            px.clear();
            py.clear();
            edges.clear();
            
            dfs(cand[i]);
            
            if (edges < com.edges) {
                com = {edges, px, py};
            }
        }
        
        coms.push_back(com);
    }
    
    std::sort(coms.begin(), coms.end());
    return coms;
}
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector a(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
    std::vector b(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> b[i][j];
        }
    }
    
    int flip = 0;
    if (n > m) {
        flip = 1;
        a = transpose(a);
        b = transpose(b);
    }
    
    auto f = work(a);
    auto g = work(b);
    
    if (f.size() != g.size()) {
        std::cout << "-1\n";
        return 0;
    }
    
    std::vector<int> tox(n, -1), toy(m, -1);
    
    for (int i = 0; i < int(f.size()); i++) {
        if (f[i].edges != g[i].edges || f[i].px.size() != g[i].px.size() || f[i].py.size() != g[i].py.size()) {
            std::cout << "-1\n";
            return 0;
        }
        if (!flip) {
            for (int j = 0; j < int(f[i].px.size()); j++) {
                tox[f[i].px[j]] = g[i].px[j];
            }
            for (int j = 0; j < int(f[i].py.size()); j++) {
                toy[f[i].py[j]] = g[i].py[j];
            }
        } else {
            for (int j = 0; j < int(f[i].py.size()); j++) {
                tox[f[i].py[j]] = g[i].py[j];
            }
            for (int j = 0; j < int(f[i].px.size()); j++) {
                toy[f[i].px[j]] = g[i].px[j];
            }
        }
    }
    
    std::vector<std::array<int, 3>> ans;
    for (int i = 0; i < n; i++) {
        while (tox[i] != i) {
            ans.push_back({0, i, tox[i]});
            std::swap(tox[i], tox[tox[i]]);
        }
    }
    for (int i = 0; i < m; i++) {
        while (toy[i] != i) {
            ans.push_back({1, i, toy[i]});
            std::swap(toy[i], toy[toy[i]]);
        }
    }
    
    std::cout << ans.size() << "\n";
    for (auto [x, y, z] : ans) {
        std::cout << x + 1 << " " << y + 1 << " " << z + 1 << "\n";
    }
    
    return 0;
}
