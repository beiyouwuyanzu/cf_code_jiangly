// url:https://codeforces.com/contest/1530/problem/F
// time:2021-07-17 18:29:45
// name:F-Bingo

#include <bits/stdc++.h>

constexpr int P = 31607;
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
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    const auto inv = Z(10000).inv();
    
    std::vector a(n, std::vector<Z>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            std::cin >> x;
            a[i][j] = x * inv;
        }
    }
    
    Z ans = 1;
    
    for (int md = 0; md <= 1; md++) {
        for (int ad = 0; ad <= 1; ad++) {
            auto b = a;
            
            Z res = ((md + ad) % 2 == 0 ? -1 : 1);
            
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if ((md && i == j) || (ad && i + j == n - 1)) {
                        res *= b[i][j];
                        b[i][j] = 1;
                    }
                }
            }
            
            std::function<void(int, std::vector<Z>, Z)> dfs = [&](int r, std::vector<Z> v, Z coef) {
                if (r == n) {
                    for (int i = 0; i < n; i++) {
                        coef *= 1 - v[i];
                    }
                    ans += coef;
                    return;
                }
                Z tmp = -coef;
                for (int i = 0; i < n; i++) {
                    tmp *= b[r][i];
                }
                dfs(r + 1, v, tmp);
                for (int i = 0; i < n; i++) {
                    v[i] *= b[r][i];
                }
                dfs(r + 1, v, coef);
            };
            dfs(0, std::vector<Z>(n, 1), res);
        }
    }
    
    std::cout << ans.val() << "\n";
    
    return 0;
}
