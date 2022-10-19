// url:https://codeforces.com/contest/1517/problem/E
// time:2021-04-23 18:39:17
// name:E-GroupPhoto

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int P = 998244353;
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
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n);
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
        }
        if (n == 1) {
            std::cout << "1\n";
            continue;
        }
        i64 ans = 0;
        for (int p = 0; p < 2; p++) {
            for (int c = 0; c < 2; c++) {
                int delta = 0;
                if (c) {
                    delta += a.back();
                }
                if (p) {
                    delta -= a[0];
                }
                int L = p, R = n - c;
                std::vector<i64> pre(n + 1), alt(n + 1);
                pre[L] = 0;
                for (int i = L; i < R; i++) {
                    pre[i + 1] = pre[i] + a[i];
                }
                for (int i = L; i < R; i++) {
                    alt[i + 1] = a[i] - alt[i];
                }
                std::vector<i64> x(n), y(n);
                std::vector<i64> v;
                for (int i = L + 1; i < R; i++) {
                    x[i] = delta + pre[i] - alt[i];
                    y[i] = pre[R] - pre[i] - alt[i];
                    v.push_back(x[i]);
                    v.push_back(y[i]);
                }
                std::sort(v.begin(), v.end());
                v.erase(std::unique(v.begin(), v.end()), v.end());
                int m = v.size();
                Fenwick<int> T[2] {Fenwick<int>(m), Fenwick<int>(m)};
                for (int i = L + 1; i < R; i++) {
                    x[i] = std::lower_bound(v.begin(), v.end(), x[i]) - v.begin();
                    y[i] = std::lower_bound(v.begin(), v.end(), y[i]) - v.begin();
                }
                for (int i = L + 1; i < R; i++) {
                    T[i % 2].add(x[i], 1);
                    ans += T[i % 2].sum(y[i]);
                }
                if (!c && !p) {
                    for (int i = 0; i <= n; i++) {
                        if (pre[n] - pre[i] < pre[i]) {
                            ans++;
                        }
                    }
                }
            }
        }
        ans %= P;
        std::cout << ans << "\n";
    }
    return 0;
}

