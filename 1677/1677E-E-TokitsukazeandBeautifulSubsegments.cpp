// url:https://codeforces.com/contest/1677/problem/E
// time:2022-05-08 18:53:21
// name:E-TokitsukazeandBeautifulSubsegments

#include <bits/stdc++.h>

using i64 = long long;
template <typename T>
struct Fenwick {
    const int n;
    std::vector<T> a;
    Fenwick(int n) : n(n), a(n) {}
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    T sum(int x) {
        T ans = 0;
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> p(n), pos(n + 1);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
        pos[p[i]] = i;
    }
    
    std::vector<std::vector<int>> div(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            div[j].push_back(i);
        }
    }
    
    std::vector<int> L(n), R(n);
    std::vector<int> s{-1};
    for (int i = 0; i < n; i++) {
        while (s.size() > 1 && p[i] > p[s.back()]) {
            s.pop_back();
        }
        L[i] = s.back() + 1;
        s.push_back(i);
    }
    s = {n};
    for (int i = n - 1; i >= 0; i--) {
        while (s.size() > 1 && p[i] > p[s.back()]) {
            s.pop_back();
        }
        R[i] = s.back() - 1;
        s.push_back(i);
    }
    
    std::vector<std::array<int, 3>> c;
    std::vector<std::array<int, 2>> a, b;
    for (int i = 0; i < n; i++) {
        a.clear();
        b.clear();
        for (auto x : div[p[i]]) {
            int u = pos[x];
            int v = pos[p[i] / x];
            if (u >= v) {
                continue;
            }
            u = std::min(u, i);
            v = std::max(v, i);
            if (L[i] <= u && v <= R[i]) {
                a.push_back({u, v});
            }
        }
        std::sort(a.begin(), a.end());
        for (auto [x, y] : a) {
            while (!b.empty() && y <= b.back()[1]) {
                b.pop_back();
            }
            if (b.empty() || x > b.back()[0]) {
                b.push_back({x, y});
            }
        }
        
        if (!b.empty()) {
            for (int i = 0; i < int(b.size()); i++) {
                c.push_back({b[i][0], b[i][1], 1});
                if (i > 0) {
                    c.push_back({b[i - 1][0], b[i][1], -1});
                }
            }
            if (L[i] > 0) {
                c.push_back({L[i] - 1, b[0][1], -1});
            }
            if (R[i] + 1 < n) {
                c.push_back({b.back()[0], R[i] + 1, -1});
            }
            if (L[i] > 0 && R[i] + 1 < n) {
                c.push_back({L[i] - 1, R[i] + 1, 1});
            }
        }
    }
    
    std::sort(c.begin(), c.end(), std::greater());
    
    std::vector<std::array<int, 3>> qry(q);
    for (int i = 0; i < q; i++) {
        int l, r;
        std::cin >> l >> r;
        l--;
        r--;
        qry[i] = {l, r, i};
    }
    std::sort(qry.begin(), qry.end(), std::greater());
    
    std::vector fen(4, Fenwick<i64>(n));
    std::vector<i64> ans(q);
    
    int j = 0;
    for (auto [l, r, i] : qry) {
        while (j < int(c.size()) && c[j][0] >= l) {
            auto [x, y, f] = c[j];
            fen[0].add(y, f * (x + 1));
            fen[1].add(y, 1LL * f * (x + 1) * (y - 1));
            fen[2].add(y, f);
            fen[3].add(y, f * (y - 1));
            j++;
        }
        ans[i] = fen[0].sum(r + 1) * r - fen[1].sum(r + 1) - fen[2].sum(r + 1) * l * r + fen[3].sum(r + 1) * l;
    }
    
    for (int i = 0; i < q; i++) {
        std::cout << ans[i] << "\n";
    }
    
    return 0;
}
