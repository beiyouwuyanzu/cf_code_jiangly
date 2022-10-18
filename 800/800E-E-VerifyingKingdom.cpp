//url:https://codeforces.com/contest/800/problem/E
//time:2021-01-03 17:13:26
//name:E-VerifyingKingdom

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
char query(int a, int b, int c) {
    std::cout << a + 1 << " " << b + 1 << " " << c + 1 << std::endl;
    char ans;
    std::cin >> ans;
    return ans;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> parent(2 * n - 1, -1), lc(2 * n - 1, -1), rc(2 * n - 1, -1);
    parent[0] = n;
    parent[1] = n;
    lc[n] = 0;
    rc[n] = 1;
    std::vector<bool> vis;
    std::vector<int> siz(2 * n - 1);
    std::function<void(int)> dfs = [&](int u) {
        siz[u] = 1;
        for (auto v : {lc[u], rc[u]}) {
            if (v < n || vis[v]) {
                continue;
            }
            dfs(v);
            siz[u] += siz[v];
        }
    };
    std::function<int(int, int)> find = [&](int u, int s) {
        for (auto v : {lc[u], rc[u]}) {
            if (v < n || vis[v]) {
                continue;
            }
            if (2 * siz[v] > s) {
                return find(v, s);
            }
        }
        return u;
    };
    std::function<int(int, int)> solve = [&](int u, int w) {
        if (vis[u] || u < n) {
            return u;
        }
        dfs(u);
        int x = find(u, siz[u]);
        int lleaf = x, rleaf = x;
        while (lleaf >= n) {
            lleaf = lc[lleaf];
        }
        while (rleaf >= n) {
            rleaf = rc[rleaf];
        }
        vis[x] = true;
        auto ans = query(lleaf, rleaf, w);
        if (ans == 'X') {
            if (x == u) {
                return x;
            }
            return solve(u, w);
        } else if (ans == 'Y') {
            return solve(rc[x], w);
        } else {
            return solve(lc[x], w);
        }
    };
    int root = n;
    for (int x = 2; x < n; x++) {
        vis.assign(2 * n - 1, false);
        int u = solve(root, x);
        int v = x + n - 1;
        if (root == u) {
            root = v;
        } else if (u == lc[parent[u]]) {
            lc[parent[u]] = v;
        } else {
            rc[parent[u]] = v;
        }
        parent[v] = parent[u];
        lc[v] = x;
        rc[v] = u;
        parent[u] = v;
        parent[x] = v;
    }
    std::cout << -1 << std::endl;
    for (int i = 0; i < 2 * n - 1; i++) {
        std::cout << parent[i] + (parent[i] >= 0);
        if (i < 2 * n - 2) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}
