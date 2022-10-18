//url:https://codeforces.com/contest/1622/problem/D
//time:2022-06-09 16:05:09
//name:D-Shuffle

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
    
    int n, k;
    std::cin >> n >> k;
    
    if (k == 0) {
        std::cout << "1\n";
        return 0;
    }
    
    std::string s;
    std::cin >> s;
    
    std::vector<Z> fac(n + 1), invfac(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i;
    }
    invfac[n] = fac[n].inv();
    for (int i = n; i > 0; i--) {
        invfac[i - 1] = invfac[i] * i;
    }
    
    std::vector<int> p{ -1 };
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            p.push_back(i);
        }
    }
    p.push_back(n);
    
    if (k > int(p.size()) - 2) {
        std::cout << "1\n";
        return 0;
    }
    
    auto binom = [&](int n, int m) {
        return fac[n] * invfac[m] * invfac[n - m];
    };
    
    Z ans = 0;
    for (int i = 0; i + k + 1 < int(p.size()); i++) {
        ans += binom(p[i + k + 1] - p[i] - 1, k);
    }
    
    for (int i = 1; i + k + 1 < int(p.size()); i++) {
        ans -= binom(p[i + k] - p[i] - 1, k - 1);
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
