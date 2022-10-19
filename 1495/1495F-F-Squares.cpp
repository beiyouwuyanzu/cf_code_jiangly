// url:https://codeforces.com/contest/1495/problem/F
// time:2021-03-10 18:10:23
// name:F-Squares

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
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
    std::vector<int> p(n + 1);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
    }
    p[n] = n + 1;
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    std::vector<i64> s(n + 1);
    for (int i = 0; i < n; i++) {
        s[i + 1] = s[i] + a[i];
    }
    std::vector<int> r(n);
    std::vector<int> stk{n};
    for (int i = n - 1; i >= 0; i--) {
        while (p[stk.back()] < p[i]) {
            stk.pop_back();
        }
        r[i] = stk.back();
        stk.push_back(i);
    }
    std::vector<int> parent(n, -1), last(n);
    stk.clear();
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && r[stk.back()] < r[i]) {
            stk.pop_back();
        }
        if (!stk.empty()) {
            parent[i] = stk.back();
        }
        stk.push_back(i);
    }
    std::vector<i64> f(n);
    for (int i = n - 1; i >= 0; i--) {
        f[i] = std::min({f[i], 0ll, b[i] - (s[r[i]] - s[i])});
        if (parent[i] != -1) {
            f[parent[i]] += f[i];
        }
    }
    for (int i = 0; i < n; i++) {
        if (parent[i] != -1) {
            f[parent[i]] -= f[i];
        }
    }
    std::vector<i64> d(q);
    std::set<int> must{0, n};
    i64 ans = s[n];
    Fenwick<i64> fen(n + 1);
    std::vector<std::tuple<int, int, int, int>> qry;
    qry.emplace_back(0, n, 0, 1);
    for (int i = 0; i < q; i++) {
        int x;
        std::cin >> x;
        x--;
        if (x == 0) {
            continue;
        }
        if (must.count(x)) {
            auto it = must.erase(must.find(x));
            int l = *std::prev(it);
            int r = *it;
            qry.emplace_back(l, x, i, -1);
            qry.emplace_back(x, r, i, -1);
            qry.emplace_back(l, r, i, 1);
        } else {
            auto it = must.insert(x).first;
            int l = *std::prev(it);
            int r = *std::next(it);
            qry.emplace_back(l, r, i, -1);
            qry.emplace_back(l, x, i, 1);
            qry.emplace_back(x, r, i, 1);
        }
    }
    std::sort(qry.begin(), qry.end(), std::greater<>());
    int x = n;
    for (auto [L, R, i, c] : qry) {
        while (x > L) {
            x--;
            fen.add(r[x], f[x]);
        }
        d[i] += fen.sum(R + 1) * c;
    }
    for (int i = 0; i < q; i++) {
        ans += d[i];
        std::cout << ans << "\n";
    }
    return 0;
}

