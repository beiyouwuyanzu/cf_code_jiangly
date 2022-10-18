//url:https://codeforces.com/contest/1615/problem/F
//time:2021-12-24 20:49:31
//name:F-LEGOndaryGrandmaster

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

void solve() {
    int n;
    std::cin >> n;
    
    std::string s, t;
    std::cin >> s >> t;
    
    std::vector<Z> f(4 * n + 1), g(4 * n + 1);
    f[2 * n] = 1;
    
    for (int i = 0; i < n; i++) {
        std::vector<Z> nf(4 * n + 1), ng(4 * n + 1);
        for (int x : {0, 1}) {
            if (s[i] == !x + '0') {
                continue;
            }
            for (int y : {0, 1}) {
                if (t[i] == !y + '0') {
                    continue;
                }
                for (int j = 2 * n - 2 * i; j <= 2 * n + 2 * i; j++) {
                    int nj = j + (i & 1 ? -1 : 1) * ((x ? 1 : -1) - (y ? 1 : -1));
                    nf[nj] += f[j];
                    ng[nj] += g[j];
                }
            }
        }
        for (int j = 0; j <= 4 * n; j++) {
            ng[j] += nf[j] * std::abs(j - 2 * n);
        }
        f = nf;
        g = ng;
    }
    
    std::cout << (g[2 * n] / 2).val() << "\n";
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

