//url:https://codeforces.com/contest/1503/problem/E
//time:2021-04-03 19:19:52
//name:E-2-Coloring

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
constexpr int P = 998244353;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    if (n == 1 || m == 1) {
        std::cout << "0\n";
        return 0;
    }
    int N = n + m;
    std::vector<std::vector<int>> C(N + 1, std::vector<int>(N + 1));
    for (int i = 0; i <= N; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
        }
    }
    int ans = 0;
    for (int x = 1; x < m; x++) {
        std::vector<int> f(n), g(n);
        for (int i = 0; i < n - 1; i++) {
            f[i] = i64(C[m - x + i][i]) * C[m - x + n - i - 2][n - i - 1] % P;
            g[i] = i64(C[x + i][i]) * C[x + n - i - 2][n - i - 1] % P;
        }
        for (int i = 1; i < n; i++) {
            g[i] = (g[i] + g[i - 1]) % P;
        }
        for (int i = 0; i < n - 1; i++) {
            ans = (ans + i64(f[i]) * g[n - 2 - i]) % P;
        }
    }
    std::swap(n, m);
    for (int x = 1; x < m; x++) {
        std::vector<int> f(n), g(n);
        for (int i = 0; i < n - 1; i++) {
            f[i] = i64(C[m - x + i][i]) * C[m - x + n - i - 2][n - i - 1] % P;
            g[i] = i64(C[x + i][i]) * C[x + n - i - 2][n - i - 1] % P;
        }
        for (int i = 1; i < n; i++) {
            g[i] = (g[i] + g[i - 1]) % P;
        }
        for (int i = 0; i < n - 2; i++) {
            ans = (ans + i64(f[i]) * g[n - 3 - i]) % P;
        }
    }
    ans = 2 * ans % P;
    std::cout << ans << "\n";
    return 0;
}

