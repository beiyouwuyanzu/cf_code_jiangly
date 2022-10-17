//url:https://codeforces.com/contest/1725/problem/K
//time:2022-09-04 17:45:02
//name:K-KingdomofCriticism

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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::map<int, int> lead;
    
    int q;
    std::cin >> q;
    
    int cnt = 0;
    std::vector<int> cur(n), value(n + q);
    
    DSU dsu(n + q);
    for (int i = 0; i < n; i++) {
        cur[i] = cnt++;
        value[cur[i]] = a[i];
        if (lead.contains(a[i])) {
            dsu.merge(lead[a[i]], cur[i]);
        } else {
            lead[a[i]] = cur[i];
        }
    }
    
    for (int i = 0; i < q; i++) {
        int o;
        std::cin >> o;
        
        if (o == 1) {
            int x, y;
            std::cin >> x >> y;
            x--;
            cur[x] = cnt++;
            value[cur[x]] = y;
            if (lead.contains(y)) {
                dsu.merge(lead[y], cur[x]);
            } else {
                lead[y] = cur[x];
            }
        } else if (o == 2) {
            int x;
            std::cin >> x;
            x--;
            
            std::cout << value[dsu.leader(cur[x])] << "\n";
        } else {
            int l, r;
            std::cin >> l >> r;
            
            for (auto it = lead.lower_bound(l); it != lead.end() && it->first <= r; it = lead.erase(it)) {
                int v;
                if (it->first <= (l + r) / 2) {
                    v = l - 1;
                } else {
                    v = r + 1;
                }
                if (lead.contains(v)) {
                    dsu.merge(lead[v], it->second);
                } else {
                    value[it->second] = v;
                    lead[v] = it->second;
                }
            }
        }
    }
    
    return 0;
}
