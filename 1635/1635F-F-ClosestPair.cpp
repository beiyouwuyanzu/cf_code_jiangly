// url:https://codeforces.com/contest/1635/problem/F
// time:2022-02-20 18:42:20
// name:F-ClosestPair

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
        T ans;
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
};

struct Min {
    i64 x;
    Min(i64 x = 9E18) : x(x) {}
};

Min &operator+=(Min &a, const Min &b) {
    a.x = std::min(a.x, b.x);
    return a;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> x(n), w(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> w[i];
    }
    
    Fenwick<Min> fen(n);
    std::vector<std::vector<std::pair<int, int>>> qry(n);
    std::vector<std::vector<int>> a(n);
    std::vector<i64> ans(q);
    for (int i = 0; i < q; i++) {
        int l, r;
        std::cin >> l >> r;
        l--;
        qry[l].emplace_back(r, i);
    }
    
    std::vector<int> s;
    for (int i = 0; i < n; i++) {
        while (!s.empty() && w[i] <= w[s.back()]) {
            s.pop_back();
        }
        if (!s.empty()) {
            a[s.back()].push_back(i);
        }
        s.push_back(i);
    }
    s.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && w[i] < w[s.back()]) {
            s.pop_back();
        }
        if (!s.empty()) {
            a[i].push_back(s.back());
        }
        s.push_back(i);
    }
    
    for (int i = n - 1; i >= 0; i--) {
        for (auto j : a[i]) {
            fen.add(j, 1LL * (x[j] - x[i]) * (w[i] + w[j]));
        }
        for (auto [r, j] : qry[i]) {
            ans[j] = fen.sum(r).x;
        }
    }
    
    for (int i = 0; i < q; i++) {
        std::cout << ans[i] << "\n";
    }
    
    return 0;
}
