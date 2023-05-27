// url:https://codeforces.com/contest/707/problem/D
// time:2023-03-15 09:48:40
// name:D-PersistentBookcase

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, q;
    std::cin >> n >> m >> q;
    
    std::vector<std::vector<std::array<int, 4>>> adj(q + 1);
    for (int i = 0; i < q; i++) {
        int t;
        std::cin >> t;
        if (t == 1) {
            int x, y;
            std::cin >> x >> y;
            x--, y--;
            adj[i].push_back({t, i + 1, x, y});
        } else if (t == 2) {
            int x, y;
            std::cin >> x >> y;
            x--, y--;
            adj[i].push_back({t, i + 1, x, y});
        } else if (t == 3) {
            int x;
            std::cin >> x;
            x--;
            adj[i].push_back({t, i + 1, x});
        } else {
            int x;
            std::cin >> x;
            adj[x].push_back({t, i + 1});
        }
    }
    
    std::vector<std::bitset<1000>> a(n);
    std::bitset<1000> b {};
    for (int i = 0; i < m; i++) {
        b[i] = 1;
    }
    
    std::vector<int> ans(q + 1);
    std::function<void(int)> dfs = [&](int i) {
        for (auto [t, j, x, y] : adj[i]) {
            if (t == 1) {
                int v = a[x][y];
                a[x][y] = 1;
                ans[j] = ans[i] + 1 - v;
                dfs(j);
                a[x][y] = v;
            } else if (t == 2) {
                int v = a[x][y];
                a[x][y] = 0;
                ans[j] = ans[i] - v;
                dfs(j);
                a[x][y] = v;
            } else if (t == 3) {
                int v = a[x].count();
                a[x] ^= b;
                ans[j] = ans[i] + m - 2 * v;
                dfs(j);
                a[x] ^= b;
            } else {
                ans[j] = ans[i];
                dfs(j);
            }
        }
    };
    dfs(0);
    
    for (int i = 1; i <= q; i++) {
        std::cout << ans[i] << "\n";
    }
    
    return 0;
}

