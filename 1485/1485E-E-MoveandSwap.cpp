// url:https://codeforces.com/contest/1485/problem/E
// time:2021-02-12 18:30:30
// name:E-MoveandSwap

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr i64 inf = 1e18;
void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::vector<std::vector<int>> e(n);
    for (int i = 1; i < n; i++) {
        int u;
        std::cin >> u;
        u--;
        e[u].push_back(i);
        e[i].push_back(u);
    }
    for (int i = 1; i < n; i++) {
        std::cin >> a[i];
    }
    std::vector<int> parent(n), dep(n);
    parent[0] = -1;
    std::function<void(int)> dfs = [&](int u) {
        for (auto v : e[u]) {
            if (v == parent[u]) {
                continue;
            }
            dep[v] = dep[u] + 1;
            parent[v] = u;
            dfs(v);
        }
    };
    dfs(0);
    int d = *std::max_element(dep.begin(), dep.end());
    std::vector<std::vector<int>> g(d + 1);
    for (int i = 0; i < n; i++) {
        g[dep[i]].push_back(i);
    }
    std::vector<i64> dp(n);
    for (int i = d; i >= 0; i--) {
        i64 mn = inf, mx = -inf;
        int rmn = 1e9, rmx = -1e9;
        for (auto u : g[i]) {
            rmn = std::min(rmn, a[u]);
            rmx = std::max(rmx, a[u]);
            for (auto v : e[u]) {
                if (v == parent[u]) {
                    continue;
                }
                mn = std::min(mn, a[u] - dp[v]);
                mx = std::max(mx, a[u] + dp[v]);
            }
        }
        mn = std::min<i64>(mn, rmn);
        mx = std::max<i64>(mx, rmx);
        for (auto u : g[i]) {
            dp[u] = std::max(a[u] - mn, mx - a[u]);
            for (auto v : e[u]) {
                if (v == parent[u]) {
                    continue;
                }
                dp[u] = std::max(dp[u], dp[v] + std::max(a[u] - rmn, rmx - a[u]));
            }
        }
    }
    std::cout << dp[0] << "\n";
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
