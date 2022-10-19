// url:https://codeforces.com/contest/1621/problem/G
// time:2022-01-03 19:27:48
// name:G-WeightedIncreasingSubsequences

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
T power(T a, int b) {
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
};

struct Info {
    int mx;
    Z cntmx;
    Z cnt;
};

Info operator+(const Info &a, const Info &b) {
    if (a.mx > b.mx) {
        return {a.mx, a.cntmx, a.cnt + b.cnt};
    } else if (a.mx < b.mx) {
        return {b.mx, b.cntmx, a.cnt + b.cnt};
    } else {
        return {a.mx, a.cntmx + b.cntmx, a.cnt + b.cnt};
    }
}

constexpr int N = 1 << 19;

Info info[N];

void pull(int p) {
    info[p] = info[2 * p] + info[2 * p + 1];
}

void build(int p, int l, int r) {
    info[p] = {-1, 0, 0};
    if (r - l == 1) {
        return;
    }
    int m = (l + r) / 2;
    build(2 * p, l, m);
    build(2 * p + 1, m, r);
    pull(p);
}

void modify(int p, int l, int r, int x, Info v) {
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

Info rangeSum(int p, int l, int r, int x, int y) {
    if (l >= y || r <= x) {
        return {-1, 0, 0};
    }
    if (l >= x && r <= y) {
        return info[p];
    }
    int m = (l + r) / 2;
    return rangeSum(2 * p, l, m, x, y) + rangeSum(2 * p + 1, m, r, x, y);
    pull(p);
}

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<std::pair<int, int>> v;
    for (int i = 0; i < n; i++) {
        v.emplace_back(a[i], -i);
    }
    std::sort(v.begin(), v.end());
    for (int i = 0; i < n; i++) {
        a[i] = std::lower_bound(v.begin(), v.end(), std::pair(a[i], -i)) - v.begin();
    }
    
    build(1, 0, n);
    
    Z ans = 0;
    std::vector<Z> f(n);
    for (int i = n - 1; i >= 0; i--) {
        auto s = Info{i, 1, 1} + rangeSum(1, 0, n, a[i], n);
        modify(1, 0, n, a[i], s);
        f[i] = s.cnt - s.cntmx;
    }
    
    build(1, 0, n);
    
    for (int i = 0; i < n; i++) {
        auto s = Info{i, 1, 1} + rangeSum(1, 0, n, 0, a[i]);
        modify(1, 0, n, a[i], s);
        ans += f[i] * s.cnt;
    }
    
    std::cout << ans.val() << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}

