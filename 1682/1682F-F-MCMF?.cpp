// url:https://codeforces.com/contest/1682/problem/F
// time:2022-05-22 18:46:13
// name:F-MCMF?

#include <bits/stdc++.h>

constexpr int P = 1000000007;
using i64 = long long;
// assume -P <= x < 2P
int norm(int x) {
    if (x < 0) {
        x += P;
    }
    if (x >= P) {
        x -= P;
    }
    return x;
}
template<class T>
T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
struct Z {
    int x;
    Z(int x = 0) : x(norm(x)) {}
    Z(i64 x) : x(norm(x % P)) {}
    int val() const {
        return x;
    }
    Z operator-() const {
        return Z(norm(P - x));
    }
    Z inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }
    Z &operator*=(const Z &rhs) {
        x = i64(x) * rhs.x % P;
        return *this;
    }
    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream &operator>>(std::istream &is, Z &a) {
        i64 v;
        is >> v;
        a = Z(v);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Z &a) {
        return os << a.val();
    }
};
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
    
    std::vector<int> a(n);
    std::vector<i64> b(n + 1);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = n - 1; i > 0; i--) {
        a[i] -= a[i - 1];
    }
    
    for (int i = 1; i <= n; i++) {
        std::cin >> b[i];
        b[i] += b[i - 1];
    }
    
    std::vector<std::array<i64, 4>> qry(q);
    for (int i = 0; i < q; i++) {
        int l, r;
        std::cin >> l >> r;
        l--;
        qry[i] = {b[l], l, r, i};
    }
    std::sort(qry.begin(), qry.end());
    
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j) { return b[i] < b[j]; });
    
    Fenwick<Z> sp(n), cp(n), sn(n), cn(n);
    for (int i = 0; i < n; i++) {
        sp.add(i, Z(b[i]) * a[i]);
        cp.add(i, a[i]);
    }
    std::vector<Z> ans(q);
    
    int j = 0;
    for (auto [v, l, r, i] : qry) {
        while (j < n && b[p[j]] <= v) {
            int k = p[j++];
            sp.add(k, -Z(b[k]) * a[k]);
            cp.add(k, -a[k]);
            sn.add(k, Z(b[k]) * a[k]);
            cn.add(k, a[k]);
        }
        
        ans[i] = sp.rangeSum(l, r) - sn.rangeSum(l, r) + (cn.rangeSum(l, r) - cp.rangeSum(l, r)) * v;
    }
    
    for (auto x : ans) {
        std::cout << x << "\n";
    }
    
    return 0;
}

