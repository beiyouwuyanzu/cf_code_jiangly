// url:https://codeforces.com/contest/1670/problem/F
// time:2022-05-06 19:08:03
// name:F-Jee,YouSee?

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
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    i64 l, r, z;
    std::cin >> n >> l >> r >> z;
    
    std::vector<Z> choose(n + 1);
    choose[0] = 1;
    for (int i = 1; i <= n; i++) {
        choose[i] = choose[i - 1] * (n - i + 1) / i;
    }
    
    auto solve = [&](i64 r) {
        std::vector<Z> dp(n + 1);
        dp[0] = 1;
        for (int i = 59; i >= 0; i--) {
            int d = r >> i & 1;
            int u = z >> i & 1;
            std::vector<Z> g(n + 1);
            for (int j = 0; j <= n; j++) {
                int k = 2 * j + d;
                for (int x = u; x <= n && x <= k; x += 2) {
                    int l = std::min(n, k - x);
                    g[l] += dp[j] * choose[x];
                }
            }
            dp = g;
        }
        return std::accumulate(dp.begin(), dp.end(), Z(0));
    };
    
    std::cout << (solve(r) - solve(l - 1)).val() << "\n";
    
    return 0;
}
