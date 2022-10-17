//url:https://codeforces.com/contest/1511/problem/E
//time:2022-09-22 14:19:51
//name:E-ColoringsandDominoes

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

const Z inv2 = Z(2).inv();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    int w = 0;
    
    std::vector<std::string> s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
        w += std::count(s[i].begin(), s[i].end(), 'o');
    }
    
    const int N = std::max(n, m);
    
    std::vector<Z> f(N + 1);
    f[0] = 1;
    f[1] = inv2;
    for (int i = 2; i <= N; i++) {
        f[i] = f[i - 2] * inv2 * inv2 + inv2;
    }
    
    Z ans = 0;
    
    for (int i = 0; i < n; i++) {
        int z = 0;
        for (int j = 0; j < m - 1; j++) {
            if (s[i][j] == 'o' && s[i][j + 1] == 'o') {
                ans += f[z];
            }
            z = (s[i][j] == 'o') ? z + 1 : 0;
        }
    }
    
    for (int j = 0; j < m; j++) {
        int z = 0;
        for (int i = 0; i < n - 1; i++) {
            if (s[i][j] == 'o' && s[i + 1][j] == 'o') {
                ans += f[z];
            }
            z = (s[i][j] == 'o') ? z + 1 : 0;
        }
    }
    
    ans *= power(Z(2), w) * inv2 * inv2;
    std::cout << ans << "\n";
    
    return 0;
}
