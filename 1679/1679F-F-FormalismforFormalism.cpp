// url:https://codeforces.com/contest/1679/problem/F
// time:2022-05-16 15:56:54
// name:F-FormalismforFormalism

#include <bits/stdc++.h>

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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    int m;
    std::cin >> m;
    
    std::array<int, 10> bad {};
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i != j) {
                bad[i] |= 1 << j;
            }
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        bad[u] ^= 1 << v;
        bad[v] ^= 1 << u;
    }
    
    std::array<Z, 1 << 10> f {};
    f.back() = 1;
    for (int i = 0; i < n; i++) {
        std::array<Z, 1 << 10> g {};
        for (int s = 0; s < (1 << 10); s++) {
            for (int i = 0; i < 10; i++) {
                if (s >> i & 1) {
                    int t = (s & ~((1 << i) - 1)) | bad[i];
                    g[t] += f[s];
                }
            }
        }
        f = g;
    }
    
    auto ans = std::accumulate(f.begin(), f.end(), Z(0));
    
    std::cout << ans << "\n";
    
    return 0;
}
