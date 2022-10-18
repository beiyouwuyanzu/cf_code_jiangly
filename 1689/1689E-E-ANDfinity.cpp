//url:https://codeforces.com/contest/1689/problem/E
//time:2022-06-10 20:13:48
//name:E-ANDfinity

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
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    auto work = [&](auto a) {
        DSU dsu(30);
        std::vector<bool> use(30);
        
        int ans = 0;
        int t = 30;
        
        for (int i = 0; i < n; i++) {
            if (a[i] == 0) {
                a[i]++;
                ans++;
            }
            int x = __builtin_ctz(a[i]);
            for (int j = x; j < 30; j++) {
                if (a[i] >> j & 1) {
                    use[j] = true;
                    dsu.merge(x, j);
                }
            }
            t = std::min(t, x);
        }
        
        bool ok = true;
        for (int i = 0; i < 30; i++) {
            if (use[i] && !dsu.same(t, i)) {
                ok = false;
            }
        }
        
        if (ok) {
            return std::pair(ans, a);
        }
        
        for (int i = 0; i < n; i++) {
            int x = __builtin_ctz(a[i]);
            if (t > 0) {
                t = 0;
                a[i]++;
                ans++;
                dsu.merge(0, x);
            }
            
            if (!dsu.same(0, x)) {
                a[i]++;
                ans++;
                dsu.merge(0, x);
            }
        }
        
        return std::pair(ans, a);
    };
    
    auto ans = work(a);
    
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            continue;
        }
        
        a[i]--;
        auto res = work(a);
        a[i]++;
        
        res.first++;
        if (res.first < ans.first) {
            ans = res;
        }
    }
    
    std::cout << ans.first << "\n";
    for (int i = 0; i < n; i++) {
        std::cout << ans.second[i] << " \n"[i == n - 1];
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

