// url:https://codeforces.com/contest/1619/problem/G
// time:2021-12-20 18:23:26
// name:G-UnusualMinesweeper

#include <bits/stdc++.h>

using i64 = long long;

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

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> x(n), y(n), t(n);
    
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i] >> t[i];
    }
    
    DSU g(n);
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j) {
        return x[i] != x[j] ? x[i] < x[j] : y[i] < y[j];
    });
    for (int i = 0; i < n - 1; i++) {
        int a = p[i], b = p[i + 1];
        if (x[a] == x[b] && y[b] - y[a] <= k) {
            g.merge(a, b);
        }
    }
    std::sort(p.begin(), p.end(), [&](int i, int j) {
        return y[i] != y[j] ? y[i] < y[j] : x[i] < x[j];
    });
    for (int i = 0; i < n - 1; i++) {
        int a = p[i], b = p[i + 1];
        if (y[a] == y[b] && x[b] - x[a] <= k) {
            g.merge(a, b);
        }
    }
    
    std::vector<int> mint(n, 1E9 + 1);
    for (int i = 0; i < n; i++) {
        int j = g.leader(i);
        mint[j] = std::min(mint[j], t[i]);
    }
    std::vector<int> a;
    for (int i = 0; i < n; i++) {
        if (g.leader(i) == i) {
            a.push_back(mint[i]);
        }
    }
    
    std::sort(a.begin(), a.end());
    
    int ans = 0;
    a.pop_back();
    
    while (!a.empty() && a.back() > ans) {
        a.pop_back();
        ans++;
    }
    
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}

