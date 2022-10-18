//url:https://codeforces.com/contest/1606/problem/F
//time:2022-06-10 12:31:41
//name:F-TreeQueries

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    int q;
    std::cin >> q;
    
    std::vector<int> ans(n);
    
    std::vector<std::vector<std::array<int, 2>>> query(n);
    
    for (int i = 0; i < q; i++) {
        int v, k;
        std::cin >> v >> k;
        v--;
        query[v].push_back({ k, i });
    }
    
    std::vector<std::vector<std::array<int, 2>>> f(n);
    
    auto merge = [&](auto a, auto b) {
        std::vector<std::array<int, 2>> c;
        int i = 0, j = 0;
        while (i < int(a.size()) && j < int(b.size())) {
            if (1LL * a[i][0] * b[j][1] < 1LL * b[j][0] * a[i][1]) {
                c.push_back(a[i++]);
            } else if (1LL * a[i][0] * b[j][1] > 1LL * b[j][0] * a[i][1]) {
                c.push_back(b[j++]);
            } else {
                c.push_back({ a[i][0] + b[j][0], a[i][1] + b[j][1] });
                i++;
                j++;
            }
        }
        while (i < int(a.size())) {
            c.push_back(a[i++]);
        }
        while (j < int(b.size())) {
            c.push_back(b[j++]);
        }
        return c;
    };
    
    std::function<void(int, int)> dfs = [&](int u, int p) {
        int deg = 0;
        for (auto v : adj[u]) {
            if (v == p) {
                continue;
            }
            deg++;
            dfs(v, u);
            f[u] = merge(f[u], f[v]);
        }
        
        for (auto [k, i] : query[u]) {
            ans[i] = deg;
            for (auto [x, c] : f[u]) {
                ans[i] += std::max(0LL, x - 1LL * k * c);
            }
        }
        
        int x = deg - 1;
        int c = 1;
        while (!f[u].empty() && 1LL * x * f[u].back()[1] <= 1LL * f[u].back()[0] * c) {
            x += f[u].back()[0];
            c += f[u].back()[1];
            f[u].pop_back();
        }
        if (x > 0) {
            f[u].push_back({ x, c });
        }
    };
    dfs(0, -1);
    
    for (int i = 0; i < q; i++) {
        std::cout << ans[i] << "\n";
    }
    
    return 0;
}

