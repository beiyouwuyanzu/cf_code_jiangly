//url:https://codeforces.com/contest/793/problem/D
//time:2021-01-03 18:06:04
//name:D-PresentsinBankopolis

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int inf = 1e9;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k;
    std::cin >> n >> k;
    int m;
    std::cin >> m;
    std::vector<int> u(m), v(m), c(m);
    std::vector<std::vector<int>> f(n, std::vector<int>(n, inf));
    for (int i = 0; i < m; i++) {
        std::cin >> u[i] >> v[i] >> c[i];
        u[i]--;
        v[i]--;
        std::swap(u[i], v[i]);
    }
    for (int i = 0; i < n; i++) {
        f[i][i] = 0;
    }
    for (int t = 0; t < k - 1; t++) {
        std::vector<std::vector<int>> g(n, std::vector<int>(n, inf));
        for (int i = 0; i < m; i++) {
            if (u[i] < v[i]) {
                for (int j = 0; j < v[i]; j++) {
                    g[v[i]][std::min(u[i], j)] = std::min(g[v[i]][std::min(u[i], j)], f[u[i]][j] + c[i]);
                }
            } else {
                for (int j = v[i] + 1; j < n; j++) {
                    g[v[i]][std::max(u[i], j)] = std::min(g[v[i]][std::max(u[i], j)], f[u[i]][j] + c[i]);
                }
            }
        }
        f = std::move(g);
    }
    int ans = inf;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans = std::min(ans, f[i][j]);
        }
    }
    if (ans >= inf) {
        ans = -1;
    }
    std::cout << ans << "\n";
    return 0;
}

