//url:https://codeforces.com/contest/1550/problem/D
//time:2021-07-14 18:02:00
//name:D-ExcellentArrays

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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    while (t--) {
        int n, l, r;
        std::cin >> n >> l >> r;
        l--;
        r--;
        
        std::vector<Z> fac(n + 1), invfac(n + 1);
        fac[0] = 1;
        for (int i = 1; i <= n; i++) {
            fac[i] = fac[i - 1] * i;
        }
        invfac[n] = fac[n].inv();
        for (int i = n; i > 0; i--) {
            invfac[i - 1] = invfac[i] * i;
        }
        
        auto binom = [&](int n, int m) {
            if (m < 0 || n < m) {
                return Z(0);
            }
            
            return fac[n] * invfac[m] * invfac[n - m];
        };
        
        int e = std::min(-l, r - (n - 1));
        
        Z ans = binom(n, n / 2) * (1 + n % 2) * e;
        
        for (int x = e + 1; ; x++) {
            int a = std::min(n, n - (l + x));
            int b = std::min(n, r - x + 1);
            if (a < 0 || b < 0) {
                break;
            }
            
            ans += binom(a + b - n, n / 2 - (n - b));
            if (n % 2 == 1) {
                ans += binom(a + b - n, n / 2 - (n - a));
            }
        }
        
        std::cout << ans.val() << "\n";
    }
    
    return 0;
}

