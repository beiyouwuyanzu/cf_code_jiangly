//url:https://codeforces.com/contest/1726/problem/G
//time:2022-09-07 06:04:51
//name:G-ACertainMagicalParty

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
};
template<class Info, class Tag>
struct LazySegmentTree {
    const int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    LazySegmentTree(int n) : n(n), info(4 << std::__lg(n)), tag(4 << std::__lg(n)) {}
    LazySegmentTree(std::vector<Info> init) : LazySegmentTree(init.size()) {
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
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
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
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n, l, r, v);
    }
};

constexpr int inf = 1E9;

struct Tag {
    int x = 0;
    
    void apply(const Tag &t) {
        x += t.x;
    }
};

struct Max {
    int x = -inf;
    int index = -1;
    
    void apply(const Tag &t) {
        x += t.x;
    }
};

Max operator+(const Max &a, const Max &b) {
    if (a.x > b.x) {
        return a;
    } else {
        return b;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<int> b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    
    std::vector<int> a0, a1;
    for (int i = 0; i < n; i++) {
        if (b[i] == 0) {
            a0.push_back(a[i]);
        } else {
            a1.push_back(a[i]);
        }
    }
    
    std::sort(a0.begin(), a0.end());
    std::sort(a1.begin(), a1.end());
    
    std::vector<Z> fac(n + 1), invfac(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i;
    }
    invfac[n] = fac[n].inv();
    for (int i = n; i; i--) {
        invfac[i - 1] = invfac[i] * i;
    }
    
    if (a1.empty()) {
        if (a0[0] == a0.back()) {
            std::cout << fac[n] << "\n";
        } else {
            std::cout << 0 << "\n";
        }
        return 0;
    }
    
    std::sort(a.begin(), a.end());
    
    int x = 0;
    for (int i = 0; auto v : a1) {
        while (i < n && a[i] <= v) {
            i++;
        }
        x = std::max(x, v + n - i);
    }
    
    for (int i = 0; i < n; i++) {
        if (a[i] > x) {
            std::cout << 0 << "\n";
            return 0;
        }
    }
    
    std::vector<std::array<int, 2>> v0, v1;
    for (int i = 0; i < int(a0.size()); ) {
        int j = i;
        while (j < int(a0.size()) && a0[i] == a0[j]) {
            j++;
        }
        v0.push_back({a0[i], j - i});
        i = j;
    }
    for (int i = 0; i < int(a1.size()); ) {
        int j = i;
        while (j < int(a1.size()) && a1[i] == a1[j]) {
            j++;
        }
        v1.push_back({a1[i], j - i});
        i = j;
    }
    
    LazySegmentTree<Max, Tag> seg(x + 1);
    
    Z ans = 1;
    
    int used = 0;
    if (!v0.empty() && v0.back()[0] == x) {
        used += v0.back()[1];
        ans *= fac[v0.back()[1]];
    }
    if (!v1.empty() && v1.back()[0] == x) {
        used += v1.back()[1];
        ans *= fac[n] * invfac[n - v1.back()[1]];
    }
    
    for (auto [v, c] : v1) {
        if (v < x) {
            seg.modify(v, {v, v});
        }
    }
    for (auto [v, c] : v1) {
        seg.rangeApply(0, v, {c});
    }
    for (auto [v, c] : v0) {
        seg.rangeApply(0, v, {c});
    }
    
    int i = 0;
    
    while (used < n) {
        int value = -1, type = -1, cnt = 0;
        if (i < int(v0.size()) && v0[i][0] < x) {
            auto [v, c] = v0[i];
            
            int big = seg.rangeQuery(v - 1, v).x;
            if (big < 0) {
                big += inf;
            } else {
                big -= v - 1;
            }
            int small = n - big;
            if (v + small == x) {
                value = v;
                type = 0;
                cnt = c;
            }
        }
        
        auto info = seg.rangeQuery(0, x + 1);
        if (info.x == x) {
            int v = info.index;
            
            auto it = std::lower_bound(v1.begin(), v1.end(), std::array{v, 0});
            int c = (*it)[1];
            
            if (v >= value) {
                value = v;
                type = 1;
                cnt = c;
            }
        }
        
        if (value == -1) {
            std::cout << 0 << "\n";
            return 0;
        }
        
        if (type == 1 && cnt > 1) {
            std::cout << 0 << "\n";
            return 0;
        }
        
        ans *= fac[cnt];
        used += cnt;
    
        if (type == 0) {
            i++;
        } else {
            seg.modify(value, {x - value - inf, -1});
        }
        
        seg.rangeApply(value, x, {cnt});
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
