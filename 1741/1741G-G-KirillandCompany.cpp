// url:https://codeforces.com/contest/1741/problem/G
// time:2022-10-11 18:20:03
// name:G-KirillandCompany

#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1E9;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    int f;
    std::cin >> f;
    
    std::vector<int> h(f);
    for (int i = 0; i < f; i++) {
        std::cin >> h[i];
        h[i]--;
    }
    
    int k;
    std::cin >> k;
    for (int i = 0; i < k; i++) {
        int p;
        std::cin >> p;
        p--;
        std::swap(h[i], h[p]);
    }
    
    auto bfs = [&](int s) {
        std::vector<int> d(n, -1);
        std::queue<std::array<int, 2>> q;
        q.push({s, 0});
        while (!q.empty()) {
            auto [x, v] = q.front();
            q.pop();
            if (d[x] != -1) {
                continue;
            }
            d[x] = v;
            for (auto y : adj[x]) {
                q.push({y, v + 1});
            }
        }
        return d;
    };
    
    auto d0 = bfs(0);
    std::sort(h.begin(), h.begin() + k, [&](int i, int j) {
        return d0[i] < d0[j];
    });
    std::vector<std::vector<int>> d(k);
    for (int i = 0; i < k; i++) {
        d[i] = bfs(h[i]);
    }
    
    std::vector<int> dp(1 << k);
    dp[0] = 1;
    
    for (int i = k; i < f; i++) {
        std::vector<int> good(1 << k);
        for (int s = 1; s < (1 << k); s++) {
            int lst = -1;
            int dist = 0;
            for (int i = 0; i < k; i++) {
                if (s >> i & 1) {
                    if (lst == -1) {
                        dist += d0[h[i]];
                    } else {
                        dist += d[lst][h[i]];
                    }
                    lst = i;
                }
            }
            dist += d[lst][h[i]];
            if (dist == d0[h[i]]) {
                good[s] = 1;
            }
        }
        
        for (int s = (1 << k) - 1; s; s--) {
            for (int t = s; t; t = (t - 1) & s) {
                dp[s] |= dp[s ^ t] & good[t];
            }
        }
    }
    
    int ans = k;
    for (int i = 0; i < (1 << k); i++) {
        if (dp[i]) {
            ans = std::min(ans, k - __builtin_popcount(i));
        }
    }
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

