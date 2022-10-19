// url:https://codeforces.com/contest/1679/problem/D
// time:2022-05-16 15:24:28
// name:D-TossaCointoYourGraph...

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    i64 k;
    std::cin >> n >> m >> k;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
    }
    
    int l = 0, r = 1E9 + 1;
    while (l < r) {
        int x = (l + r) / 2;
        int cnt = 0;
        std::vector<int> deg(n), q;
        for (int i = 0; i < n; i++) {
            if (a[i] > x) {
                continue;
            }
            cnt++;
            for (auto v : adj[i]) {
                if (a[v] <= x) {
                    deg[v]++;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (a[i] <= x && !deg[i]) {
                q.push_back(i);
            }
        }
        
        std::vector<int> dp(n);
        for (int i = 0; i < int(q.size()); i++) {
            int u = q[i];
            dp[u] = std::max(dp[u], 1);
            for (auto v : adj[u]) {
                if (a[v] > x) {
                    continue;
                }
                dp[v] = std::max(dp[v], dp[u] + 1);
                if (!--deg[v]) {
                    q.push_back(v);
                }
            }
        }
        
        if (cnt > int(q.size()) || *std::max_element(dp.begin(), dp.end()) >= k) {
            r = x;
        } else {
            l = x + 1;
        }
    }
    
    if (r > 1E9) {
        std::cout << "-1\n";
    } else {
        std::cout << r << "\n";
    }
    
    return 0;
}
