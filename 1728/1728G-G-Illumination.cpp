//url:https://codeforces.com/contest/1728/problem/G
//time:2022-09-08 19:00:48
//name:G-Illumination

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
struct Event {
    int t;
    Z x0;
    Z x1;
};

bool operator<(const Event &a, const Event &b) {
    return a.t < b.t;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int d, n, m;
    std::cin >> d >> n >> m;
    
    std::vector<int> l(n), p(m);
    for (int i = 0; i < n; i++) {
        std::cin >> l[i];
    }
    for (int i = 0; i < m; i++) {
        std::cin >> p[i];
    }
    
    std::sort(l.begin(), l.end());
    std::sort(p.begin(), p.end());
    
    std::vector<int> cnt(d + 1);
    for (int i = 0; i < n; i++) {
        cnt[l[i] + 1]++;
    }
    for (int i = 1; i <= d; i++) {
        cnt[i] += cnt[i - 1];
    }
    
    std::vector prod(m, std::vector<Z>(n + 1)), inv(m, std::vector<Z>(n + 1));
    for (int i = 0; i < m; i++) {
        prod[i][0] = 1;
        for (int j = 0; j < n; j++) {
            prod[i][j + 1] = prod[i][j] * std::abs(l[j] - p[i]);
        }
        inv[i][n] = prod[i][n].inv();
        for (int j = n - 1; j >= 0; j--) {
            inv[i][j] = inv[i][j + 1] * std::abs(l[j] - p[i]);
        }
    }
    
    std::vector<Event> events;
    for (int s = 0; s < (1 << m); s++) {
        if (s == 0) {
            events.push_back({0, power(Z(d + 1), n + 1), 0});
        } else {
            int last = -1, pos = 0;
            Z res = __builtin_parity(s) ? -1 : 1;
            for (int i = 0; i < m; i++) {
                if (~s >> i & 1) {
                    continue;
                }
                if (last == -1) {
                    last = i;
                } else {
                    int np = (p[last] + p[i] + 1) / 2;
                    np = cnt[np];
                    res *= prod[last][np] * inv[last][pos];
                    pos = np;
                    last = i;
                }
            }
            res *= prod[last][n] * inv[last][pos];
            
            last = -1;
            pos = 0;
            Z x0 = 0, x1 = 0;
            
            for (int i = 0; i < m; i++) {
                if (~s >> i & 1) {
                    continue;
                }
                if (last != -1) {
                    int np = (p[last] + p[i] + 1) / 2;
                    Z nx0 = res * -p[last];
                    Z nx1 = res;
                    events.push_back({pos, nx0 - x0, nx1 - x1});
                    x0 = nx0, x1 = nx1, pos = np;
                }
                Z nx0 = res * p[i];
                Z nx1 = -res;
                events.push_back({pos, nx0 - x0, nx1 - x1});
                x0 = nx0, x1 = nx1, pos = p[i];
                last = i;
            }
            Z nx0 = res * -p[last];
            Z nx1 = res;
            events.push_back({pos, nx0 - x0, nx1 - x1});
        }
    }
    
    std::sort(events.begin(), events.end());
    
    int q;
    std::cin >> q;
    
    std::vector<std::array<int, 2>> qry(q);
    for (int i = 0; i < q; i++) {
        int f;
        std::cin >> f;
        qry[i] = {f, i};
    }
    
    std::sort(qry.begin(), qry.end());
    
    std::vector<Z> ans(q);
    
    Z x0 = 0, x1 = 0;
    for (int j = 0; auto [f, i] : qry) {
        while (j < int(events.size()) && events[j].t <= f) {
            x0 += events[j].x0;
            x1 += events[j].x1;
            j++;
        }
        ans[i] = x0 + f * x1;
    }
    
    for (int i = 0; i < q; i++) {
        std::cout << ans[i] << "\n";
    }
    
    return 0;
}
