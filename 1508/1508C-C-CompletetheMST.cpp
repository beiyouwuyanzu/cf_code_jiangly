// url:https://codeforces.com/contest/1508/problem/C
// time:2021-04-16 18:16:44
// name:C-CompletetheMST

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
constexpr i64 inf = 1e18;
struct DSU {
    std::vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return leader(x) == leader(y); }
    bool merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[leader(x)]; }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    i64 cm = i64(n) * (n - 1) / 2 - m;
    DSU t(n);
    std::vector<int> u(m), v(m), w(m);
    std::vector<std::vector<int>> e(n);
    for (int i = 0; i < m; i++) {
        std::cin >> u[i] >> v[i] >> w[i];
        u[i]--;
        v[i]--;
        e[u[i]].push_back(v[i]);
        e[v[i]].push_back(u[i]);
    }
    int comp = 0;
    std::set<int> S;
    for (int i = 0; i < n; i++) {
        S.insert(i);
    }
    for (int s = 0; s < n; s++) {
        if (S.count(s)) {
            comp++;
            std::queue<int> que;
            que.push(s);
            S.erase(s);
            while (!que.empty()) {
                int u = que.front();
                que.pop();
                t.merge(u, s);
                std::sort(e[u].begin(), e[u].end());
                e[u].push_back(n);
                auto it = S.begin();
                for (auto v : e[u]) {
                    while (it != S.end() && *it < v) {
                        que.push(*it);
                        it = S.erase(it);
                    }
                    if (it != S.end() && *it == v) {
                        it++;
                    }
                }
            }
        }
    }
    int xsum = 0;
    int mn = 1 << 30;
    i64 total = 0;
    for (int i = 0; i < m; i++) {
        xsum ^= w[i];
    }
    std::vector<int> p(m);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j) {
        return w[i] < w[j];
    });
    DSU t2(n);
    for (auto i : p) {
        if (t.merge(u[i], v[i])) {
            total += w[i];
            t2.merge(u[i], v[i]);
        }
    }
    for (int i = 0; i < m; i++) {
        if (!t2.same(u[i], v[i])) {
            mn = std::min(mn, w[i]);
        }
    }
    if (cm == n - comp) {
        total += std::min(xsum, mn);
    }
    std::cout << total << "\n";
    return 0;
}
