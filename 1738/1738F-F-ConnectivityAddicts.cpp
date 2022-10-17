//url:https://codeforces.com/contest/1738/problem/F
//time:2022-09-30 18:17:16
//name:F-ConnectivityAddicts

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
    
    std::vector<int> d(n);
    for (int i = 0; i < n; i++) {
        std::cin >> d[i];
    }
    
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j) {
        return d[i] > d[j];
    });
    
    std::vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        pos[p[i]] = i;
    }
    
    DSU dsu(n);
    for (auto x : p) {
        while (dsu.leader(x) == x && dsu.size(x) < d[x]) {
            std::cout << "? " << x + 1 << std::endl;
            int y;
            std::cin >> y;
            y--;
            if (pos[y] < pos[x]) {
                dsu.merge(y, x);
            } else {
                dsu.merge(x, y);
            }
        }
    }
    
    std::cout << "!";
    for (int i = 0; i < n; i++) {
        std::cout << " " << dsu.leader(i) + 1;
    }
    std::cout << std::endl;
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
