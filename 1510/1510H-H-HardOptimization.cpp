// url:https://codeforces.com/contest/1510/problem/H
// time:2021-04-07 16:18:53
// name:H-HardOptimization

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
constexpr int N = 2000;
using Array = i64[N + 1][2][2];
constexpr i64 inf = 1e18;
int n;
i64 dp[N][N + 1][2][2], h[N][N + 1][2][2], beg[N][N + 1][2][2];
int l[N], r[N];
int siz[N];
std::vector<int> e[N];
std::vector<Array *> g[N];
void dfs(int u) {
    siz[u] = 1;
    for (int i = 0; i <= N; i++) {
        for (int p = 0; p < 2; p++) {
            for (int q = 0; q < 2; q++) {
                beg[u][i][p][q] = -inf;
            }
        }
    }
    for (int p = 0; p < 2; p++) {
        for (int q = 0; q < 2; q++) {
            beg[u][0][p][q] = (p - q) * l[u];
        }
    }
    g[u].push_back(&beg[u]);
    for (auto v : e[u]) {
        dfs(v);
        siz[u] += siz[v];
        auto &y = *g[u].back();
        for (int i = 0; i <= N; i++) {
            for (int p = 0; p < 2; p++) {
                for (int q = 0; q < 2; q++) {
                    h[v][i][p][q] = v == e[u][0] && siz[v] <= i && i <= 2 * siz[v] ? dp[v][i][p][q] : -inf;
                }
            }
            if (i <= 2 * siz[u]) {
                for (int j = siz[v]; j <= i && j <= 2 * siz[v]; j++) {
                    for (int p = 0; p < 2; p++) {
                        for (int q = 0; q < 2; q++) {
                            h[v][i][p][q] = std::max({h[v][i][p][q], y[i - j][p][0] + dp[v][j][0][q], i == j ? -inf : y[i - j - 1][p][1] + dp[v][j][1][q]});
                        }
                    }
                }
            }
        }
        g[u].push_back(&h[v]);
    }
    auto &y = *g[u].back();
    for (int i = siz[u]; i <= 2 * siz[u] && i <= N; i++) {
        for (int p = 0; p < 2; p++) {
            for (int q = 0; q < 2; q++) {
                dp[u][i][p][q] = std::max(std::max(y[i][p][0], y[i - 1][p][1] + r[u]) - q * r[u], y[i][p][q]);
            }
        }
    }
}
std::vector<int> Ls(n), Rs(n);
void track(int u, int s, int p, int q) {
    assert(siz[u] <= s && s <= 2 * siz[u]);
    int deg = e[u].size();
    auto &y = *g[u][deg];
    int val = dp[u][s][p][q];
    if (val == y[s][p][0] - q * r[u]) {
        val = y[s][p][0];
        if (q == 1) {
            Ls.push_back(r[u]);
        }
        q = 0;
    } else if (val == y[s - 1][p][1] + (1 - q) * r[u]) {
        val = y[s - 1][p][1];
        Rs.push_back(r[u]);
        if (q == 1) {
            Ls.push_back(r[u]);
        }
        q = 1;
        s--;
    } else {
        assert(val == y[s][p][q]);
    }
    for (int i = deg - 1; i >= 0; i--) {
        auto &y = *g[u][i];
        int v = e[u][i];
        if (i == 0 && siz[v] <= s && s <= 2 * siz[v] && val == dp[v][s][p][q]) {
            track(v, s, p, q);
            return;
        } else {
            for (int j = siz[v]; j <= s && j <= 2 * siz[v]; j++) {
                if (val == y[s - j][p][0] + dp[v][j][0][q]) {
                    val = y[s - j][p][0];
                    track(v, j, 0, q);
                    q = 0;
                    s -= j;
                    break;
                } else if (val == (s == j ? -inf : y[s - j - 1][p][1] + dp[v][j][1][q])) {
                    val = y[s - j - 1][p][1];
                    track(v, j, 1, q);
                    q = 1;
                    s -= j + 1;
                    break;
                }
            }
        }
    }
    if (p == 1) {
        Rs.push_back(l[u]);
    }
    if (q == 1) {
        Ls.push_back(l[u]);
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> l[i] >> r[i];
    }
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j) {
        return l[i] < l[j];
    });
    std::vector<int> parent(n);
    for (int i = 0; i < n; i++) {
        parent[p[i]] = -1;
        for (int j = i - 1; j >= 0; j--) {
            if (r[p[j]] > r[p[i]]) {
                parent[p[i]] = p[j];
                break;
            }
        }
        if (parent[p[i]] != -1) {
            e[parent[p[i]]].push_back(p[i]);
        }
    }
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        if (parent[i] == -1) {
            dfs(i);
            ans += dp[i][siz[i]][0][0];
            track(i, siz[i], 0, 0);
        }
    }
    std::sort(Ls.begin(), Ls.end());
    std::sort(Rs.begin(), Rs.end());
    std::vector<int> L(n, -1), R(n);
    assert(int(L.size()) == n);
    assert(int(R.size()) == n);
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j >= 0; j--) {
            if (L[p[j]] == -1 && l[p[j]] <= Ls[i] && Rs[i] <= r[p[j]]) {
                L[p[j]] = Ls[i];
                R[p[j]] = Rs[i];
                break;
            }
        }
    }
    std::cout << ans << "\n";
    for (int i = 0; i < n; i++) {
        std::cout << L[i] << " " << R[i] << "\n";
    }
    return 0;
}

