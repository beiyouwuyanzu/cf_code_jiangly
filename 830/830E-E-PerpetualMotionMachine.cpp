//url:https://codeforces.com/contest/830/problem/E
//time:2021-03-31 06:32:01
//name:E-PerpetualMotionMachine

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> e(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    std::vector<bool> vis(n);
    std::vector<int> parent(n, -1);
    std::vector<int> ans(n);
    std::function<bool(int)> dfs = [&](int u) {
        vis[u] = true;
        for (auto v : e[u]) {
            if (v == parent[u]) {
                continue;
            }
            if (vis[v]) {
                for (int i = u; i != parent[v]; i = parent[i]) {
                    ans[i] = 1;
                }
                return true;
            }
            parent[v] = u;
            if (dfs(v)) {
                return true;
            }
        }
        return false;
    };
    for (int i = 0; i < n; i++) {
        if (!vis[i] && dfs(i)) {
            std::cout << "YES\n";
            for (int j = 0; j < n; j++) {
                std::cout << ans[j] << " \n"[j == n - 1];
            }
            return;
        }
    }
    for (int i = 0; i < n; i++) {
        if (e[i].size() >= 4) {
            ans[i] = 2;
            for (int j = 0; j < 4; j++) {
                ans[e[i][j]] = 1;
            }
            std::cout << "YES\n";
            for (int j = 0; j < n; j++) {
                std::cout << ans[j] << " \n"[j == n - 1];
            }
            return;
        }
    }
    std::vector<int> f(n, -1);
    for (int i = 0; i < n; i++) {
        if (e[i].size() == 3) {
            for (int j = i; j != -1; j = parent[j]) {
                if (f[j] != -1) {
                    for (int u = f[j]; u != j; u = parent[u]) {
                        ans[u] = 2;
                    }
                    for (int u = i; u != parent[j]; u = parent[u]) {
                        ans[u] = 2;
                    }
                    int k = 2;
                    for (auto v : e[f[j]]) {
                        if (ans[v] == 0 && k > 0) {
                            ans[v] = 1;
                            k--;
                        }
                    }
                    k = 2;
                    for (auto v : e[i]) {
                        if (ans[v] == 0 && k > 0) {
                            ans[v] = 1;
                            k--;
                        }
                    }
                    std::cout << "YES\n";
                    for (int j = 0; j < n; j++) {
                        std::cout << ans[j] << " \n"[j == n - 1];
                    }
                    return;
                }
                f[j] = i;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (e[i].size() == 3) {
            std::vector<int> x[3];
            for (int j = 0; j < 3; j++) {
                int u = e[i][j];
                int last = i;
                x[j].push_back(u);
                while (e[u].size() == 2) {
                    std::tie(u, last) = std::make_pair(e[u][0] ^ e[u][1] ^ last, u);
                    x[j].push_back(u);
                }
            }
            std::sort(x, x + 3, [&](const auto &a, const auto &b) {
                return a.size() < b.size();
            });
            for (auto a : {std::vector{2, 2, 2}, {1, 2, 5}, {1, 3, 3}}) {
                bool ok = true;
                for (int j = 0; j < 3; j++) {
                    if (int(x[j].size()) < a[j]) {
                        ok = false;
                    }
                }
                if (!ok) {
                    continue;
                }
                int S = std::lcm(a[0] + 1, std::lcm(a[1] + 1, a[2] + 1));
                ans[i] = S;
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < a[j]; k++) {
                        ans[x[j][k]] = S / (a[j] + 1) * (a[j] - k);
                    }
                }
                std::cout << "YES\n";
                for (int j = 0; j < n; j++) {
                    std::cout << ans[j] << " \n"[j == n - 1];
                }
                return;
            }
        }
    }
    std::cout << "NO\n";
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

