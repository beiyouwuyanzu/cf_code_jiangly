// url:https://codeforces.com/contest/1685/problem/D2
// time:2022-05-25 22:04:41
// name:D2-PermutationWeight(HardVersion)

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
    // for (int i = 0; i + 1 < n; i++) {
    //     if (!dsu.same(i, i + 1)) {
    //         int x = h[i];
    //         int y = h[i + 1];
    //         std::swap(p[x], p[y]);
    //         std::swap(h[i], h[i + 1]);
    //         dsu.merge(i, i + 1);
    //     }
    // }
    
    std::vector<int> ans(n, -1);
    
    auto check = [&]() {
        DSU g = dsu;
        
        std::vector<bool> need(n - 1);
        for (int i = 0; i < n; i++) {
            if (ans[i] != -1) {
                int x = p[ans[i]];
                if (x < i) {
                    for (int j = x; j < i; j++) {
                        need[j] = true;
                    }
                } else {
                    for (int j = i; j < x; j++) {
                        need[j] = true;
                    }
                }
            }
        }
        
        for (int i = 0; i < n - 1; i++) {
            if (need[i] && !g.merge(i, i + 1)) {
                return false;
            }
        }
        
        std::vector<int> dir(n - 2, -1);
        std::vector<bool> cant(n - 1);
        
        auto work = [&](int x, int d) {
            if (dir[x] >= 0 && dir[x] != d) {
                dir[x] = 0;
            } else {
                dir[x] = d;
            }
        };
        
        for (int i = 0; i < n; i++) {
            if (ans[i] != -1) {
                int x = p[ans[i]];
                if (x < i) {
                    for (int j = x; j + 1 < i; j++) {
                        work(j, 1);
                    }
                    if (x > 0) {
                        work(x - 1, 2);
                    }
                    if (i + 1 < n) {
                        work(i - 1, 2);
                    }
                } else if (x > i) {
                    for (int j = x - 1; j > i; j--) {
                        work(j - 1, 2);
                    }
                    if (x + 1 < n) {
                        work(x - 1, 1);
                    }
                    if (i > 0) {
                        work(i - 1, 1);
                    }
                } else {
                    if (x + 1 < n) {
                        cant[x] = true;
                    }
                    if (x > 0) {
                        cant[x - 1] = true;
                    }
                }
            }
        }
        
        for (int i = 0; i + 2 < n; i++) {
            if (need[i] && need[i + 1] && dir[i] == 0) {
                return false;
            }
        }
        for (int i = 0; i + 1 < n; i++) {
            if (need[i] && cant[i]) {
                return false;
            }
        }
        
        for (int i = 0; i < n - 1; i++) {
            if (need[i]) {
                continue;
            }
            if (cant[i]) {
                continue;
            }
            if (i > 0 && dir[i - 1] == 0) {
                continue;
            }
            if (i < n - 2 && dir[i] == 0) {
                continue;
            }
            g.merge(i, i + 1);
        }
        for (int i = 0; i < n; i++) {
            if (!g.same(0, i)) {
                return false;
            }
        }
        
        return true;
    };
    
    std::vector<bool> cyc(n);
    int cnt = 0;
    for (int i = 0; ; i = ans[i]) {
        std::cout << i + 1;
        cyc[i] = true;
        cnt++;
        
        ans[i] = 0;
        while ((cnt < n && cyc[ans[i]]) || !check()) {
            ans[i]++;
        }
        
        if (ans[i] == 0) {
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
