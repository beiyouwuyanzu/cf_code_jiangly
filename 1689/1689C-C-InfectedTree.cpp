//url:https://codeforces.com/contest/1689/problem/C
//time:2022-06-10 19:48:28
//name:C-InfectedTree

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    std::vector<int> dep(n);
    
    int ans = 0;
    std::function<void(int, int)> dfs = [&](int u, int p) {
        int deg = 0;
        for (auto v : adj[u]) {
            if (v == p) {
                continue;
            }
            dep[v] = dep[u] + 1;
            dfs(v, u);
            deg++;
        }
        
        if (deg < 2) {
            ans = std::max(ans, n - 2 * dep[u] - 1 - deg);
        }
    };
    dfs(0, -1);
    
    std::cout << ans << "\n";
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

