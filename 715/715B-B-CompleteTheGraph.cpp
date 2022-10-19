// url:https://codeforces.com/contest/715/problem/B
// time:2021-07-07 11:32:51
// name:B-CompleteTheGraph

#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 inf = 1e18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, L, s, t;
    std::cin >> n >> m >> L >> s >> t;
    
    std::vector<std::vector<std::pair<int, int>>> e(n);
    std::vector<int> w(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v >> w[i];
        e[u].emplace_back(v, i);
        e[v].emplace_back(u, i);
    }
    
    int cnt = 0;
    std::vector<int> idx(m);
    for (int i = 0; i < m; i++) {
        if (w[i] == 0) {
            idx[i] = cnt++;
        }
    }
    
    auto dijkstra = [&](int s, int t, i64 X) {
        std::vector<i64> dis(n, inf);
        std::priority_queue<std::tuple<i64, int>> h;
        h.emplace(0, s);
        while (!h.empty()) {
            auto [d, u] = h.top();
            h.pop();
            if (dis[u] < inf) {
                continue;
            }
            dis[u] = -d;
            for (auto [v, j] : e[u]) {
                i64 dv = d - (w[j] > 0 ? w[j] : (X + idx[j]) / cnt);
                h.emplace(dv, v);
            }
        }
        return dis[t];
    };
    
    if (dijkstra(s, t, i64(L + 1) * cnt) < L) {
        std::cout << "NO\n";
        return 0;
    }
    
    if (dijkstra(s, t, cnt) > L) {
        std::cout << "NO\n";
        return 0;
    }
    
    std::cout << "YES\n";
    
    i64 lo = cnt, hi = i64(L + 1) * cnt;
    while (lo < hi) {
        i64 x = (lo + hi) / 2;
        if (dijkstra(s, t, x) >= L) {
            hi = x;
        } else {
            lo = x + 1;
        }
    }
    
    for (int i = 0; i < m; i++) {
        if (w[i] == 0) {
            w[i] = (lo + idx[i]) / cnt;
        }
    }
    
    for (int u = 0; u < n; u++) {
        for (auto [v, i] : e[u]) {
            if (v > u) {
                std::cout << u << " " << v << " " << w[i] << "\n";
            }
        }
    }
    
    return 0;
}
