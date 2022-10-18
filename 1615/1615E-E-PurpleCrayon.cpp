//url:https://codeforces.com/contest/1615/problem/E
//time:2021-12-24 18:10:55
//name:E-PurpleCrayon

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k;
    std::cin >> n >> k;
    
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    std::vector<int> a;
    std::function<int(int, int)> dfs = [&](int u, int p) {
        int x = 0;
        for (auto v : adj[u]) {
            if (v == p) {
                continue;
            }
            int y = dfs(v, u);
            if (y > x) {
                std::swap(x, y);
            }
            a.push_back(y);
        }
        return x + 1;
    };
    a.push_back(dfs(0, -1));
    
    std::sort(a.begin(), a.end(), std::greater());
    a.resize(k, 0);
    
    i64 ans = -1E18;
    for (int i = 0, x = n; i <= k; i++) {
        if (i > 0) {
            x -= a[i - 1];
        }
        
        // min [b<=x] (n-i-b)(i-b)
        
        int b = std::min(n / 2, x);
        ans = std::max(ans, 1LL * (n - i - b) * (i - b));
    }
    
    std::cout << ans << "\n";
    
    return 0;
}

