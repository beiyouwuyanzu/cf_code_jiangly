// url:https://codeforces.com/contest/1491/problem/E
// time:2021-02-28 17:29:36
// name:E-Fib-tree

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int f[30], t[30];
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    f[0] = f[1] = 1;
    for (int i = 2; i < 30; i++) {
        f[i] = f[i - 2] + f[i - 1];
    }
    int n;
    std::cin >> n;
    int k = 0;
    while (f[k] < n) {
        k++;
    }
    if (f[k] != n) {
        std::cout << "NO\n";
        return 0;
    }
    std::vector<std::vector<std::pair<int, int>>> e(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        e[u].emplace_back(v, i);
        e[v].emplace_back(u, i);
    }
    std::vector<bool> vis(n - 1);
    std::vector<int> siz(n), in(n), parent(n);
    std::function<bool(int, int)> check = [&](int u, int k) {
        if (f[k] == 1) {
            return true;
        }
        int x = -1;
        std::function<void(int)> dfs = [&](int u) {
            siz[u] = 1;
            for (auto [v, i] : e[u]) {
                if (vis[i] || i == in[u]) {
                    continue;
                }
                in[v] = i;
                parent[v] = u;
                dfs(v);
                siz[u] += siz[v];
            }
            if (siz[u] == f[k - 1] || siz[u] == f[k - 2]) {
                x = u;
            }
        };
        in[u] = parent[u] = -1;
        dfs(u);
        if (x == -1) {
            return false;
        }
        assert(parent[x] != -1);
        vis[in[x]] = true;
        int y = parent[x];
        int t1 = siz[x] == f[k - 1] ? k - 1 : k - 2;
        int t2 = (k - 1) + (k - 2) - t1;
        return check(x, t1) && check(y, t2);
    };
    if (check(0, k)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}

