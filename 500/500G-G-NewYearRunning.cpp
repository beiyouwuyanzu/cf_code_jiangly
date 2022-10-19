// url:https://codeforces.com/contest/500/problem/G
// time:2021-06-23 23:45:17
// name:G-NewYearRunning

#include <bits/stdc++.h>
using i64 = long long;
constexpr i64 inf = 1e18;
i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i64 g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
i64 bet(i64 p, i64 a, i64 l, i64 r) {
    if (a == 0)
        return l == 0 ? 0 : inf;
    i64 c = (l + a - 1) / a;
    if (a * c <= r)
        return c;
    i64 b = p % a;
    i64 y = bet(a, b, a - r % a, a - l % a);
    return y == inf ? inf : (l + __int128(y) * b + a - 1) / a + p / a * y;
}
i64 G(i64 a, i64 b, i64 R, i64 m) {
    i64 x, y;
    i64 g = exgcd(b, m, x, y);
    m /= g;
    x %= m;
    if (x < 0) {
        x += m;
    }
    i64 L = __int128(a / g) * x % m;
    R += L;
    if (L / m != R / m) {
        return a % g;
    }
    L %= m;
    R %= m;
    i64 ans = bet(m, x, L, R);
    if (ans == inf) {
        return inf;
    }
    return ans * g + a % g;
}
i64 solve(int a, int b, int c, int d, int k = 0) {
    if ((d - b) % 2 != 0) {
        return inf;
    }
    i64 x, y;
    i64 g = exgcd(a, c, x, y);
    int k0 = (d - b) / 2 % (g / 2);
    if (k0 < 0) {
        k0 += g / 2;
    }
    if (k < k0) {
        return inf;
    }
    i64 x0 = i64(d - b - 2 * k0) / g * x % (c / g);
    if (x0 < 0) {
        x0 += c / g;
    }
    i64 m = i64(a) * c / g;
    i64 res = (x0 * a + b + k0) % m;
    int L = (k - k0) / (g / 2);
    i64 t = g / 2 - i64(a) * x;
    t %= m;
    if (t < m) {
        t += m;
    }
    return G(res, t, L, m);
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
    std::vector<int> parent(n, -1), dep(n), siz(n), pref(n, -1), top(n);
    std::function<void(int)> dfs1 = [&](int u) {
        siz[u] = 1;
        for (auto v : e[u]) {
            if (v == parent[u]) {
                continue;
            }
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (pref[u] == -1 || siz[v] > siz[pref[u]]) {
                pref[u] = v;
            }
        }
    };
    std::function<void(int)> dfs2 = [&](int u) {
        for (auto v : e[u]) {
            if (v == parent[u]) {
                continue;
            }
            top[v] = v == pref[u] ? top[u] : v;
            dfs2(v);
        }
    };
    dfs1(0);
    dfs2(0);
    auto lca = [&](int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    };
    auto dist = [&](int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    };
    int q;
    std::cin >> q;
    while (q--) {
        int u, v, x, y;
        std::cin >> u >> v >> x >> y;
        u--;
        v--;
        x--;
        y--;
        int duv = dist(u, v);
        int dxy = dist(x, y);
        int dux = dist(u, x);
        int duy = dist(u, y);
        int dvx = dist(v, x);
        int dvy = dist(v, y);
        i64 ans = inf;
        int T1 = 2 * duv;
        int T2 = 2 * dxy;
        if (duv + dxy == duy + dvx) {
            int A, B, C, D, E;
            C = (duv + dxy - dux - dvy) / 2;
            A = (duv + duy - dvy) / 2 - C;
            D = duv - A - C;
            B = (dxy + dvx - dvy) / 2 - C;
            E = dxy - B - C;
            ans = std::min(ans, solve(T1, A, T2, B));
            ans = std::min(ans, solve(T1, duv + D, T2, dxy + E));
            ans = std::min(ans, solve(T1, A, T2, dxy + E + C, C));
            ans = std::min(ans, solve(T1, duv + D, T2, B + C, C));
        } else if (duv + dxy == dux + dvy) {
            std::swap(x, y);
            std::swap(dux, duy);
            std::swap(dvx, dvy);
            int A, B, C, D, E;
            C = (duv + dxy - dux - dvy) / 2;
            A = (duv + duy - dvy) / 2 - C;
            D = duv - A - C;
            B = (dxy + dvx - dvy) / 2 - C;
            E = dxy - B - C;
            ans = std::min(ans, solve(T1, A, T2, dxy + B));
            ans = std::min(ans, solve(T1, duv + D, T2, E));
            ans = std::min(ans, solve(T1, A, T2, E + C, C));
            ans = std::min(ans, solve(T1, duv + D, T2, dxy + B + C, C));
        }
        if (ans == inf) {
            ans = -1;
        }
        std::cout << ans << "\n";
    }
    return 0;
}
