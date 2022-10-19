// url:https://codeforces.com/contest/1511/problem/G
// time:2021-04-13 18:21:50
// name:G-ChipsonaBoard

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
struct Query {
    int x;
    int d;
    int id;
};
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
    int n, m;
    std::cin >> n >> m;
    std::vector<int> c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> c[i];
        c[i]--;
    }
    std::sort(c.begin(), c.end());
    int D = std::__lg(m) + 1;
    int q;
    std::cin >> q;
    std::vector<int> ans(q);
    std::vector<int> l(q), r(q);
    std::vector<Query> queries;
    for (int i = 0; i < q; i++) {
        std::cin >> l[i] >> r[i];
        l[i]--;
        queries.push_back({r[i], l[i], i});
        queries.push_back({l[i], l[i], i});
    }
    std::sort(queries.begin(), queries.end(), [&](const auto &a, const auto &b) {
        return a.x < b.x;
    });
    for (int v = 0; v < D; v++) {
        std::vector<int> cnt(q);
        Fenwick<int> t(1 << (v + 1));
        int i = 0;
        for (auto query : queries) {
            while (i < n && c[i] < query.x) {
                t.add(c[i] & ((1 << (v + 1)) - 1), 1);
                i++;
            }
            int d = query.d & ((1 << (v + 1)) - 1);
            if (d >> v) {
                cnt[query.id] ^= t.rangeSum(d - (1 << v), d) & 1;
            } else {
                cnt[query.id] ^= (t.rangeSum(d + (1 << v), 1 << (v + 1)) ^ t.sum(d)) & 1;
            }
        }
        for (int i = 0; i < q; i++) {
            ans[i] |= cnt[i];
        }
    }
    for (int i = 0; i < q; i++) {
        std::cout << "BA"[ans[i]];
    }
    std::cout << "\n";
    return 0;
}
