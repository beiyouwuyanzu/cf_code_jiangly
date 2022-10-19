// url:https://codeforces.com/contest/1670/problem/E
// time:2022-05-06 18:58:05
// name:E-HemoseontheTree

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int p;
    std::cin >> p;
    
    int n = 1 << p;
    
    std::vector<std::vector<std::array<int, 2>>> adj(n);
    std::vector<int> a(n), b(n - 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }
    
    a[0] = 1 << p;
    auto dfs = [&](auto dfs, int u, int pa, int d) -> void {
        for (auto [v, j] : adj[u]) {
            if (v == pa) {
                continue;
            }
            if (d) {
                b[j] = v ^ n;
                a[v] = v;
            } else {
                b[j] = v;
                a[v] = v ^ n;
            }
            dfs(dfs, v, u, !d);
        }
    };
    dfs(dfs, 0, -1, 1);
    
    std::cout << "1\n";
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " \n"[i == n - 1];
    }
    for (int i = 0; i < n - 1; i++) {
        std::cout << b[i] << " \n"[i == n - 2];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
