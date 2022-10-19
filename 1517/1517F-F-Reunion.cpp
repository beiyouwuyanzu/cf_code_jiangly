// url:https://codeforces.com/contest/1517/problem/F
// time:2021-04-23 19:43:08
// name:F-Reunion

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int P = 998244353;
int norm(int x) {
    if (x < P) {
        return x;
    } else {
        return x - P;
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> e(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    int Inv = 1;
    for (int i = 0; i < n; i++) {
        Inv = i64(Inv) * (P + 1) / 2 % P;
    }
    int ans = n - 1;
    for (int r = 1; r <= n - 1; r++) {
        std::vector<std::vector<int>> f(n, std::vector<int>(n)), g(n, std::vector<int>(n));
        std::vector<int> h(n);
        std::function<void(int, int)> dfs = [&](int u, int p) {
            f[u][0] = 1;
            g[u][0] = 1;
            for (auto v : e[u]) {
                if (v == p) {
                    continue;
                }
                dfs(v, u);
                std::vector<int> tf(n), tg(n);
                for (int i = 0; i <= h[u]; i++) {
                    for (int j = 0; j <= h[v]; j++) {
                        int mx = std::max(i, j + 1);
                        int mn = std::min(i, j + 1);
                        tf[mx] = (tf[mx] + i64(f[u][i]) * f[v][j]) % P;
                        if (i + j + 1 <= r) {
                            tg[j + 1] = (tg[j + 1] + i64(f[u][i]) * g[v][j]) % P;
                            tg[i] = (tg[i] + i64(g[u][i]) * f[v][j]) % P;
                        } else {
                            tf[i] = (tf[i] + i64(f[u][i]) * g[v][j]) % P;
                            tf[j + 1] = (tf[j + 1] + i64(g[u][i]) * f[v][j]) % P;
                        }
                        tg[mn] = (tg[mn] + i64(g[u][i]) * g[v][j]) % P;
                    }
                }
                f[u] = tf;
                g[u] = tg;
                h[u] = std::max(h[u], h[v] + 1);
            }
        };
        dfs(0, -1);
        int sum = std::accumulate(g[0].begin(), g[0].end(), 0ll) % P;
        ans = (ans + i64(P - Inv) * sum) % P;
    }
    std::cout << ans << "\n";
    return 0;
}

