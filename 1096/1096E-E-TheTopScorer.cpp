//url:https://codeforces.com/contest/1096/problem/E
//time:2021-07-15 21:03:59
//name:E-TheTopScorer

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

constexpr int N = 1e4;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int p, r, s;
    std::cin >> p >> s >> r;
    
    std::vector<Z> fac(N + 1), invfac(N + 1), inv(N + 1);
    fac[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = fac[i - 1] * i;
    }
    invfac[N] = fac[N].inv();
    for (int i = N; i > 0; i--) {
        invfac[i - 1] = invfac[i] * i;
        inv[i] = invfac[i] * fac[i - 1];
    }
    
    auto binom = [&](int n, int m) {
        return fac[n] * invfac[m] * invfac[n - m];
    };
    
    Z ways = binom(s - r + p - 1, p - 1);
    Z sum = 0;
    
    for (int x = r; x <= s; x++) {
        for (int c = 1; c * x <= s && c <= p; c++) {
            Z res = 0;
            int v = p - c;
            for (int i = 0; (i + c) * x <= s && i + c <= p; i++) {
                int t = s - (i + c) * x;
                res += binom(p - c, i) * (i % 2 == 0 ? 1 : -1) * (v == 0 ? t == 0 : binom(t + v - 1, v - 1));
            }
            res *= binom(p - 1, c - 1);
            sum += res * inv[c];
        }
    }
    
    Z ans = sum / ways;
    
    std::cout << ans.val() << "\n";
    
    return 0;
}
