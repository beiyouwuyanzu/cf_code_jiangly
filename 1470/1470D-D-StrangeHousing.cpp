//url:https://codeforces.com/contest/1470/problem/D
//time:2021-01-05 18:28:14
//name:D-StrangeHousing

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n, m;
        std::cin >> n >> m;
        std::vector<std::vector<int>> e(n);
        std::vector<bool> vis(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            std::cin >> u >> v;
            u--;
            v--;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        std::vector<int> a;
        std::function<void(int)> dfs = [&](int u) {
            vis[u] = true;
            a.push_back(u);
            for (auto v : e[u]) {
                if (!vis[v]) {
                    dfs(v);
                }
            }
        };
        dfs(0);
        if (int(a.size()) < n) {
            std::cout << "NO\n";
            continue;
        }
        std::cout << "YES\n";
        std::vector<int> ans;
        vis.assign(n, false);
        for (auto u : a) {
            bool f = false;
            for (auto v : e[u]) {
                if (vis[v]) {
                    f = true;
                }
            }
            if (!f) {
                vis[u] = true;
                ans.push_back(u);
            }
        }
        std::cout << ans.size() << "\n";
        for (auto u : ans) {
            std::cout << u + 1 << " \n"[u == ans.back()];
        }
    }
    return 0;
}
