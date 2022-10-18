//url:https://codeforces.com/contest/827/problem/F
//time:2021-03-31 11:38:49
//name:F-DirtyArkady'sKitchen

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    if (n == 1) {
        std::cout << "0\n";
        return 0;
    }
    std::vector<std::vector<int>> e(2 * n);
    std::vector<int> to, L, R;
    auto addEdge = [&](int u, int v, int l, int r) {
        e[u].push_back(to.size());
        to.push_back(v);
        L.push_back(l);
        R.push_back(r);
        e[v].push_back(to.size());
        to.push_back(u);
        L.push_back(l);
        R.push_back(r);
    };
    for (int i = 0; i < m; i++) {
        int u, v, l, r;
        std::cin >> u >> v >> l >> r;
        u--;
        v--;
        addEdge(2 * u, 2 * v + 1, l, r);
        addEdge(2 * u + 1, 2 * v, l, r);
    }
    int M = to.size();
    std::vector<int> dp(M, -1);
    std::priority_queue<std::pair<int, int>> h;
    for (int i = 0; i < 2 * n; i++) {
        std::sort(e[i].begin(), e[i].end(), [&](int i, int j) {
            return L[i] < L[j];
        });
    }
    std::vector<int> a(2 * n);
    while (a[0] < int(e[0].size()) && L[e[0][a[0]]] == 0) {
        h.emplace(0, e[0][a[0]]);
        a[0]++;
    }
    while (!h.empty()) {
        auto [d, i] = h.top();
        h.pop();
        d = -d;
        dp[i] = d;
        if (dp[i] == R[i]) {
            continue;
        }
        int v = to[i];
        while (a[v] < int(e[v].size())) {
            int j = e[v][a[v]];
            int x = std::max(dp[i] + 1, L[j]);
            if (x % 2 != v % 2) {
                x++;
            }
            if (x > R[i]) {
                break;
            }
            if (x <= R[j]) {
                h.emplace(-x, j);
            }
            a[v]++;
        }
    }
    int ans = -1;
    for (auto u : {2 * (n - 1), 2 * n - 1}) {
        for (auto i : e[u]) {
            if (dp[i] != -1 && (ans == -1 || ans > dp[i])) {
                ans = dp[i];
            }
        }
    }
    std::cout << ans << "\n";
    return 0;
}

