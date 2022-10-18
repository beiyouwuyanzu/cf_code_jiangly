//url:https://codeforces.com/contest/765/problem/F
//time:2021-07-12 15:44:50
//name:F-Souvenirs

#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9;

struct Fenwick {
    const int n;
    std::vector<int> a;
    Fenwick(int n) : n(n), a(n, inf) {}
    void add(int x, int v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = std::min(a[i - 1], v);
        }
    }
    int query(int x) {
        int ans = inf;
        for (int i = x; i > 0; i -= i & -i) {
            ans = std::min(a[i - 1], ans);
        }
        return ans;
    }
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
    
    std::vector<std::pair<int, int>> candidates;
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j) { return a[i] < a[j]; });
    
    for (int k = 0; k <= 30; k++) {
        std::set<int> s;
        
        for (int i = 0, j = 0; i < n; i++) {
            while (j < n && a[p[j]] < a[p[i]] + (1 << k)) {
                s.insert(p[j]);
                j++;
            }
            
            auto it = s.find(p[i]);
            if (it != s.begin()) {
                candidates.emplace_back(*std::prev(it), p[i]);
            }
            if (std::next(it) != s.end()) {
                candidates.emplace_back(p[i], *std::next(it));
            }
            
            s.erase(it);
        }
    }
    
    std::sort(candidates.begin(), candidates.end(), std::greater<>());
    
    int m;
    std::cin >> m;
    
    std::vector<std::tuple<int, int, int>> queries;
    
    for (int i = 0; i < m; i++) {
        int l, r;
        std::cin >> l >> r;
        l--;
        queries.emplace_back(l, r, i);
    }
    
    std::sort(queries.begin(), queries.end(), std::greater<>());
    std::vector<int> ans(m);
    
    Fenwick fen(n);
    
    int i = 0;
    for (auto [l, r, j] : queries) {
        while (i < int(candidates.size()) && candidates[i].first >= l) {
            auto [u, v] = candidates[i];
            i++;
            fen.add(v, std::abs(a[u] - a[v]));
        }
        
        ans[j] = fen.query(r);
    }
    
    for (int i = 0; i < m; i++) {
        std::cout << ans[i] << "\n";
    }
    
    return 0;
}
