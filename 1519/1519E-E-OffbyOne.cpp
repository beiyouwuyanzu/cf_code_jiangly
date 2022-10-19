// url:https://codeforces.com/contest/1519/problem/E
// time:2022-06-27 11:51:27
// name:E-OffbyOne

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<std::array<i64, 2>> x(n), y(n);
    for (int i = 0; i < n; i++) {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        
        i64 num = 1LL * (a + b) * d;
        i64 den = 1LL * b * c;
        i64 g = std::gcd(num, den);
        x[i] = {num / g, den / g};
        
        num = 1LL * a * d;
        den = 1LL * b * (c + d);
        g = std::gcd(num, den);
        y[i] = {num / g, den / g};
    }
    
    std::map<std::array<i64, 2>, int> id;
    int V = 0;
    
    std::vector<int> u(n), v(n);
    for (int i = 0; i < n; i++) {
        if (!id.contains(x[i])) {
            id[x[i]] = V++;
        }
        u[i] = id[x[i]];
        if (!id.contains(y[i])) {
            id[y[i]] = V++;
        }
        v[i] = id[y[i]];
    }
    
    std::vector<std::vector<std::array<int, 2>>> adj(V);
    for (int i = 0; i < n; i++) {
        adj[u[i]].push_back({v[i], i});
        adj[v[i]].push_back({u[i], i});
    }
    
    std::vector<std::array<int, 2>> ans;
    std::vector<bool> vis(n), visv(V);
    
    std::function<int(int, int)> dfs = [&](int u, int e) {
        if (visv[u]) {
            return e;
        }
        visv[u] = true;
        
        int t = -1;
        for (auto [v, i] : adj[u]) {
            if (vis[i]) {
                continue;
            }
            vis[i] = true;
            int x = dfs(v, i);
            
            if (x == -1) {
                continue;
            }
            if (t == -1) {
                t = x;
            } else {
                ans.push_back({t, x});
                t = -1;
            }
        }
        
        if (e != -1 && t != -1) {
            ans.push_back({e, t});
            e = t = -1;
        }
        
        return e;
    };
    
    for (int i = 0; i < V; i++) {
        dfs(i, -1);
    }
    
    std::cout << ans.size() << "\n";
    for (auto [x, y] : ans) {
        std::cout << x + 1 << " " << y + 1 << "\n";
    }
    
    return 0;
}

