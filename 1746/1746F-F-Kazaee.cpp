// url:https://codeforces.com/contest/1746/problem/F
// time:2022-10-15 18:53:23
// name:F-Kazaee

#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

constexpr int N = 40;
template <typename T>
struct Fenwick {
    int n;
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
    int kth(T k) {
        int x = 0;
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    auto v = a;
    
    std::vector<int> o(q), l(q), r(q), k(q);
    for (int i = 0; i < q; i++) {
        std::cin >> o[i] >> l[i] >> r[i];
        l[i]--;
        if (o[i] == 2) {
            std::cin >> k[i];
        }
        v.push_back(r[i]);
    }
    
    std::sort(v.begin(), v.end());
    const int M = v.size();
    
    for (int i = 0; i < n; i++) {
        a[i] = std::lower_bound(v.begin(), v.end(), a[i]) - v.begin();
    }
    for (int i = 0; i < q; i++) {
        if (o[i] == 1) {
            r[i] = std::lower_bound(v.begin(), v.end(), r[i]) - v.begin();
        }
    }
    
    std::vector<int> ans(q, 1);
    
    for (int t = 0; t < N; t++) {
        std::vector<i64> f(M);
        for (int i = 0; i < M; i++) {
            f[i] = rng();
        }
        
        Fenwick<i64> fen(n);
        for (int i = 0; i < n; i++) {
            fen.add(i, f[a[i]]);
        }
        auto b = a;
        for (int i = 0; i < q; i++) {
            if (o[i] == 1) {
                fen.add(l[i], f[r[i]] - f[b[l[i]]]);
                b[l[i]] = r[i];
            } else {
                if (fen.rangeSum(l[i], r[i]) % k[i] != 0) {
                    ans[i] = 0;
                }
            }
        }
    }
    
    for (int i = 0; i < q; i++) {
        if (o[i] == 2) {
            std::cout << (ans[i] ? "YES" : "NO") << "\n";
        }
    }
    
    return 0;
}
