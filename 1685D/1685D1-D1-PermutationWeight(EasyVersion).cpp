//url:https://codeforces.com/contest/1685/problem/D1
//time:2022-05-25 21:29:35
//name:D1-PermutationWeight(EasyVersion)

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
    int n;
    std::cin >> n;
    
    std::vector<int> p(n), h(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
        p[i]--;
        h[p[i]] = i;
    }
    
    DSU dsu(n);
    std::vector<bool> vis(n);
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            continue;
        }
        for (int j = i; !vis[j]; j = p[j]) {
            vis[j] = true;
            dsu.merge(j, i);
        }
    }
    for (int i = 0; i + 1 < n; i++) {
        if (!dsu.same(i, i + 1)) {
            int x = h[i];
            int y = h[i + 1];
            std::swap(p[x], p[y]);
            std::swap(h[i], h[i + 1]);
            dsu.merge(i, i + 1);
        }
    }
    
    for (int i = 0; ; i = h[i]) {
        std::cout << i + 1;
        if (h[i] == 0) {
            std::cout << "\n";
            return;
        } else {
            std::cout << " ";
        }
    }
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
