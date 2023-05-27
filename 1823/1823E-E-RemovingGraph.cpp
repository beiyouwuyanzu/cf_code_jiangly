// url:https://codeforces.com/contest/1823/problem/E
// time:2023-04-28 09:18:16
// name:E-RemovingGraph

#include <bits/stdc++.h>

using i64 = long long;
struct DSU {
    std::vector<int> f, siz;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, l, r;
    std::cin >> n >> l >> r;
    
    DSU dsu(n);
    for (int i = 0; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        dsu.merge(u, v);
    }
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (dsu.find(i) == i) {
            int s = dsu.size(i);
            ans ^= s >= l + r ? 0 : s / l;
        }
    }
    
    if (ans) {
        std::cout << "Alice\n";
    } else {
        std::cout << "Bob\n";
    }
    
    return 0;
}
