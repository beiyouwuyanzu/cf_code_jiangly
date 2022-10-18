//url:https://codeforces.com/contest/1483/problem/D
//time:2021-03-21 17:03:50
//name:D-UsefulEdges

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr i64 inf = 1e18;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<i64>> e(n, std::vector<i64>(n, inf)), a(n, std::vector<i64>(n, inf));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--;
        v--;
        e[u][v] = e[v][u] = w;
    }
    a = e;
    for (int i = 0; i < n; i++) {
        a[i][i] = 0;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = std::min(a[i][j], a[i][k] + a[k][j]);
            }
        }
    }
    std::vector<std::vector<i64>> l(n, std::vector<i64>(n, inf));
    int q;
    std::cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--;
        v--;
        l[u][v] = l[v][u] = -w;
    }
    std::vector<std::vector<i64>> b(n, std::vector<i64>(n, inf));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                b[i][j] = std::min(b[i][j], a[i][k] + l[k][j]);
            }
        }
    }
    int ans = 0;
    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            if (e[u][v] < inf) {
                i64 mn = inf;
                for (int i = 0; i < n; i++) {
                    mn = std::min(mn, b[u][i] + a[i][v]);
                }
                if (mn <= -e[u][v]) {
                    ans++;
                }
            }
        }
    }
    std::cout << ans << "\n";
    return 0;
}

