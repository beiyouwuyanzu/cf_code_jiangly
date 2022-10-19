// url:https://codeforces.com/contest/1743/problem/F
// time:2022-10-17 18:16:21
// name:F-IntersectionandUnion

#include <bits/stdc++.h>

using i64 = long long;

constexpr int P = 998244353;
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
};template<class Info,
    class Merge = std::plus<Info>>
struct SegmentTree {
    const int n;
    const Merge merge;
    std::vector<Info> info;
    SegmentTree(int n) : n(n), merge(Merge()), info(4 << std::__lg(n)) {}
    SegmentTree(std::vector<Info> init) : SegmentTree(init.size()) {
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = merge(info[2 * p], info[2 * p + 1]);
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return merge(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m, r, x, y));
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
};

struct Matrix {
    Z a[2][2];
};

Matrix operator+(const Matrix &a, const Matrix &b) {
    Matrix c;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                c.a[i][j] += a.a[i][k] * b.a[k][j];
            }
        }
    }
    return c;
}

Matrix M0, M1;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    M0.a[0][0] = 3;
    M0.a[0][1] = 0;
    M0.a[1][0] = 1;
    M0.a[1][1] = 2;
    
    M1.a[0][0] = 1;
    M1.a[0][1] = 2;
    M1.a[1][0] = 1;
    M1.a[1][1] = 2;
    
    int n;
    std::cin >> n;
    
    std::vector<int> l(n), r(n);
    int max = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> l[i] >> r[i];
        max = std::max(max, r[i]);
    }
    
    max++;
    std::vector<std::vector<int>> add(max), del(max);
    for (int i = 0; i < n; i++) {
        add[l[i]].push_back(i);
        del[r[i]].push_back(i);
    }
    
    int a0 = 0;
    
    SegmentTree<Matrix> seg(std::vector(n - 1, M0));
    
    Z ans = 0;
    
    for (int i = 0; i < max; i++) {
        for (auto j : add[i]) {
            if (j) {
                seg.modify(j - 1, M1);
            } else {
                a0 = 1;
            }
        }
        ans += seg.info[1].a[a0][1];
        for (auto j : del[i]) {
            if (j) {
                seg.modify(j - 1, M0);
            } else {
                a0 = 0;
            }
        }
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
