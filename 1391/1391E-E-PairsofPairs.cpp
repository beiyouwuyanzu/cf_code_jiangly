// url:https://codeforces.com/contest/1391/problem/E
// time:2021-02-18 10:10:08
// name:E-PairsofPairs

#include <bits/stdc++.h>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n, m;
        std::cin >> n >> m;
        std::vector<std::vector<int>> e(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            std::cin >> u >> v;
            --u;
            --v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        std::vector<int> parent(n), dep(n), dfn(n, -1), a(n);
        int now = 0;
        std::function<void(int)> dfs = [&](int u) {
            dfn[u] = now++;
            a[dfn[u]] = u;
            for (auto v : e[u]) {
                if (dfn[v] == -1) {
                    parent[v] = u;
                    dep[v] = dep[u] + 1;
                    dfs(v);
                }
            }
        };
        parent[0] = -1;
        dfs(0);
        int x = std::max_element(dep.begin(), dep.end()) - dep.begin();
        if (dep[x] + 1 >= (n + 1) / 2) {
            std::cout << "PATH\n";
            std::cout << dep[x] + 1 << "\n";
            for (int i = x; i != -1; i = parent[i])
                std::cout << i + 1 << " \n"[i == 0];
            continue;
        }
        int l = (n + 3) / 4;
        x = a[n - l - 1];
        std::vector<int> vis(n);
        for (int i = parent[x]; i != -1; i = parent[i])
            vis[i] = 1;
        std::cout << "PAIRING\n";
        std::cout << l << "\n";
        for (int i = 0, j = 0; i < l; ++i) {
            while (vis[a[j]])
                ++j;
            std::cout << a[j++] + 1 << " " << a[n - l + i] + 1 << "\n";
        }
    }
    return 0;
}
