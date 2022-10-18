//url:https://codeforces.com/contest/830/problem/B
//time:2021-03-31 08:49:14
//name:B-CardsSorting

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
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
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::stable_sort(p.begin(), p.end(), [&](int i, int j) {
        return a[i] < a[j];
    });
    int last = 0;
    i64 ans = 0;
    Fenwick<int> t(n);
    for (int i = 0; i < n; i++) {
        t.add(i, 1);
    }
    for (int i = 0; i < n; ) {
        int j = i;
        int x = -1;
        int mx = -1;
        while (j < n && a[p[i]] == a[p[j]]) {
            mx = std::max(mx, p[j]);
            if (p[j] < last) {
                x = std::max(x, p[j]);
            }
            j++;
        }
        if (x == -1) {
            ans += t.rangeSum(last, mx + 1);
            last = mx + 1;
        } else {
            ans += t.rangeSum(last, n) + t.sum(x + 1);
            last = x + 1;
        }
        for (int k = i; k < j; k++) {
            t.add(p[k], -1);
        }
        i = j;
    }
    std::cout << ans << "\n";
    return 0;
}

