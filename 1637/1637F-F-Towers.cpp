// url:https://codeforces.com/contest/1637/problem/F
// time:2022-02-12 18:21:36
// name:F-Towers

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> h(n);
    for (int i = 0; i < n; i++) {
        std::cin >> h[i];
    }
    
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    int r = std::max_element(h.begin(), h.end()) - h.begin();
    
    i64 ans = h[r] * 2;
    
    auto dfs = [&](auto self, int u, int p) -> void {
        std::vector<int> a;
        for (auto v : adj[u]) {
            if (v == p) {
                continue;
            }
            self(self, v, u);
            h[u] = std::max(h[u], h[v]);
            a.push_back(h[v]);
        }
        
        std::sort(a.begin(), a.end());
        for (int i = 0; i < int(a.size()) - 1 - (u == r); i++) {
            ans += a[i];
        }
    };
    dfs(dfs, r, -1);
    
    std::cout << ans << "\n";
    
    return 0;
}
